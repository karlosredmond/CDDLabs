/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief A Semaphore Implementation to demonstrate a reusable barrier 
  \									
  \\ 

*/


#include "ReusableBarrier.h"
#include <iostream>
#include <thread>

/*
  \\Function that demonstrates reusable barrier.
*/
class ReusableBarrier;
void taskOne(ReusableBarrier rb){
	rb.Wait();
  	rb.FirstPhase();
  	rb.SecondPhase();
}


int main(void){
  std::thread threadArr[2] ;
  ReusableBarrier rb(2);
  /**< Launch the threads  */
  for(int i = 0; i < 2; i++ ){
    threadArr[i] = std::thread(taskOne, rb);
  }
  for(int i =0; i <2; i++){
    threadArr[i].join(); 
  }
      std::cout << "All Threads Finished, back in main"<< std::endl ;
  return 0;
}
