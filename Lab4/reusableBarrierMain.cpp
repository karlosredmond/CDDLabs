/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ License Employed: GNU General Public License v3.0
  \\ brief A Semaphore Implementation to demonstrate a reusable barrier 
  \									
  \\ 

*/


#include "ReusableBarrier.h"
#include <iostream>
#include <thread>
#include <mutex>

/*
  \\Function that demonstrates reusable barrier.
*/

void taskOne(std::shared_ptr<ReusableBarrier> rb){
  	std::cout << "first test" << std::endl;
  	rb->FirstPhase();
	std::cout << "second test" << std::endl;
	rb->SecondPhase();
}
/*!
  Driver to show the reusable barrier class in operation
 */

int main(void){
  int numThreads = 5;
  std::thread threadArr[numThreads] ;
  std::shared_ptr<ReusableBarrier> rb(new ReusableBarrier(numThreads));
  
  /**< Launch the threads  */
  for(int i = 0; i < numThreads; i++ ){
    threadArr[i] = std::thread(taskOne, rb);
  }
  for(int i =0; i <numThreads; i++){
    threadArr[i].join(); 
  }
  std::cout << "All Threads Finished, back in main"<< std::endl ;
  return 0;
}
