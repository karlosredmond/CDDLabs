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
  	this->mutex->Wait();
	count++;
	if(count == n){
	  this->barrierB->Wait();
	  this->barrierA->Signal();
	}
	this->mutex->Signal();
	this->barrierA->Wait();
}

void ReusableBarrier::SecondPhase(){
	std::cout << "Hello from first rendevous, Im thread "  << std::endl ;
	this->mutex->Wait();
	count--;
	if(count == 0){
	  	this->barrierA->Wait();
	  	this->barrierB->Signal();
	}
	this->mutex->Signal();
	this->barrierB->Wait();
	std::cout << "Ive made it past the second barrier"<< std::endl ;
	this->barrierB->Signal();
}

ReusableBarrier::ReusableBarrier(int count){
  	  count =  0;
	  n = count;
	  std::shared_ptr<Semaphore>  mutex(new Semaphore(1));
 	  std::shared_ptr<Semaphore>  barrierA(new Semaphore(0));
	  std::shared_ptr<Semaphore>  barrierB(new Semaphore(0));
}

	


