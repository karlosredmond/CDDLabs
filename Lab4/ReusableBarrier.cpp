/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief: ReusableBarrier Class
  \									
  \\ 

*/
#include "ReusableBarrier.h"
#include <iostream>
#include <mutex>
/*!
  FirstPhase is called to indicate that the thread has reached the first turnstile or rendezvous
 */
void ReusableBarrier::FirstPhase(){
  	mutex->Wait();
	count++;
	if(count == n){
	  barrierB->Wait();
	  barrierA->Signal();
	}
	mutex->Signal();
	barrierA->Wait();
	barrierA->Signal();
}
/*!
  Second phase is called to indicate that all the threads have executed there code and the rendezvous or turnstile is reset and ready to use again
 */
void ReusableBarrier::SecondPhase(){	
	mutex->Wait();
	count--;
	if(count == 0){
	  barrierA->Wait();
	  barrierB->Signal();
	}
	mutex->Signal();
	barrierB->Wait();
	barrierB->Signal();
}

void ReusableBarrier::Wait(){
  	FirstPhase();
  	SecondPhase();
}

ReusableBarrier::ReusableBarrier(int count){
	  n = count;
	  this->count = 0;
	  mutex=std::make_shared<Semaphore>(1);
	  barrierA=std::make_shared<Semaphore>(0);
	  barrierB=std::make_shared<Semaphore>(1);
}

	


