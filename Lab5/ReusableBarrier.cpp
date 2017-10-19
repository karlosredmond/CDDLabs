/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief: ReusableBarrier Class
  \									
  \\ 

*/
#include "ReusableBarrier.h"
#include <iostream>
class ReusableBarrier;
void ReusableBarrier::FirstPhase(){
  	ReusableBarrier::mutex->Wait();
	ReusableBarrier::count++;
	if(ReusableBarrier::count == n){
	  ReusableBarrier::barrierB->Wait();
	  ReusableBarrier::barrierA->Signal();
	}
	ReusableBarrier::mutex->Signal();
	ReusableBarrier::barrierA->Wait();
}

void SecondPhase(){
	std::cout << "Hello from first rendevous, Im thread "  << std::endl ;
	ReusableBarrier::mutex->Wait();
	ReusableBarrier::count--;
	if(ReusableBarrier::count == 0){
	  	ReusableBarrier::barrierA->Wait();
	  	ReusableBarrier::barrierB->Signal();
	}
	ReusableBarrier::mutex->Signal();
	ReusableBarrier::barrierB->Wait();
	std::cout << "Ive made it past the second barrier"<< std::endl ;
	ReusableBarrier::barrierB->Signal();
}

void Wait(){
  	FirstPhase();
	SecondPhase();
}


