/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief: ReusableBarrier Class
  \									
  \\ 

*/
#include "ReusableBarrier.h"
#include <iostream>

void ReusableBarrier::FirstPhase(){
  	mutex->Wait();
	count++;
	if(count == n){
	  barrierB->Wait();
	  barrierA->Signal();
	}
	mutex->Signal();
	barrierA->Wait();
}

void ReusableBarrier::SecondPhase(){
	std::cout << "Hello from first rendevous, Im thread "  << std::endl ;
	mutex->Wait();
	count--;
	if(count == 0){
	  	barrierA->Wait();
	  	barrierB->Signal();
	}
	mutex->Signal();
	barrierB->Wait();
	std::cout << "Ive made it past the second barrier"<< std::endl ;
       barrierB->Signal();
}

	


