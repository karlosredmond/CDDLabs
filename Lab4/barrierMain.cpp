/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief A Semaphore Implementation to demonstrate a reusable barrier 
  \									
  \\ 

*/


#include "Semaphore.h"
#include <iostream>
#include <vector>
#include <thread>

/*
  \\Function that demonstrates reusable barrier.
*/
void taskOne(std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> barrier, std::shared_ptr<Semaphore> barrierB, std::shared_ptr<int> count, std::shared_ptr<int> n){
  mutex->Wait();
  int value = *count;
  *count = *count + 1;
  if(*n==*count){
    barrierB->Wait();
    barrier->Signal();
  }
  mutex ->Signal();
  barrier->Wait();
  std::cout << "Hello from first rendevous, Im thread " << value << std::endl ;
  barrier->Signal();
  mutex->Wait();
  *count = *count - 1;
  if(*count == 0){
    barrier ->Wait();
    barrierB->Signal();
  }
  mutex->Signal();
  barrierB->Wait();
    std::cout << "Ive made it past the second barrier"<< std::endl ;
  barrierB->Signal();
}


int main(void){
  std::shared_ptr<int> count(new int(0));
  std::shared_ptr<int> n(new int(2));
  std::thread threadArr[2] ;
  std::shared_ptr<Semaphore> mutex(new Semaphore(1)) ;
  std::shared_ptr<Semaphore> barrier(new Semaphore(0));
 std::shared_ptr<Semaphore> barrierB(new Semaphore(1));
  /**< Launch the threads  */
  for(int i = 0; i < 2; i++ ){
    threadArr[i] = std::thread(taskOne, mutex, barrier, barrierB, count, n);
  }
  for(int i =0; i <2; i++){
    threadArr[i].join(); 
  }
      std::cout << "All Threads Finished, back in main"<< std::endl ;
  return 0;
}
