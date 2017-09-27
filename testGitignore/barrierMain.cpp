/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017 fu
  \\ brief A Semaphore Implementation to show mutual exclusion, where only one thread can access a resource at any time, in my case I am demonstrating it with "cout"
  \									\
  \\ Uses C++11 features such as mutex and condition variables to implement Semaphore

*/


#include "Semaphore.h"
#include <iostream>
#include <vector>
#include <thread>

int count = 0 ;
int n = 5;
int arr[5] = {1,2,3,4,5} ;
std::shared_ptr<Semaphore> mutex(new Semaphore(1)) ;
std::shared_ptr<Semaphore> barrier(new Semaphore(0));

void taskOne(){
  mutex->Wait();
  int value = count;
  count++;
  mutex ->Signal();
  
  if(n==count){
    barrier->Signal() ;
  }

  barrier->Wait();
  std::cout << "Hello from thread " << value << std::endl ;
  barrier->Signal();

}

int main(void){
  std::thread threadArr[5] ;
  /**< Launch the threads  */
  for(int i = 0; i < 5; i++ ){
    threadArr[i] = std::thread(taskOne);
  }
  for(int i = 0; i < 5; i++){
    threadArr[i].join();
  }

  return 0;
}
