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
	std::shared_ptr<Semaphore>  mutex(new Semaphore(1));
	std::shared_ptr<Semaphore>  barrierA(new Semaphore(0));
	std::shared_ptr<Semaphore>  barrierB(new Semaphore(0));
	void Wait();
	void ReusabelBarrier::FirstPhase();
	void SecondPhase();
	ReusableBarrier(int count){
	  count =  0;
	  n = count;
	}
	
};
