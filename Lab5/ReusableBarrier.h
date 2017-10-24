/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief: ReusableBarrier.h
  \									
  \\ 

*/


#include <mutex>
#include "Semaphore.h"

class ReusableBarrier{
public:
 	int count;
	int n;
	std::shared_ptr<Semaphore>  mutex;
	std::shared_ptr<Semaphore>  barrierA;
	std::shared_ptr<Semaphore>  barrierB;
	void Wait();
	void FirstPhase();
	void SecondPhase();
	ReusableBarrier(int count){
	  count =  0;
	  n = count;
	  std::shared_ptr<Semaphore>  mutex(new Semaphore(1));
 	  std::shared_ptr<Semaphore>  barrierA(new Semaphore(0));
	  std::shared_ptr<Semaphore>  barrierB(new Semaphore(0));
	}
	
};
