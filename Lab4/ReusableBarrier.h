/*! 
  \\ Author: Karl Redmond
  \\ Date: 10th Oct 2017
  \\ brief: ReusableBarrier.h
  \									
  \\ 

*/


#include <mutex>
#include "Semaphore.h"
/*!
  Class used to implement a rendezvous with more than two threads, meaning N threads will have to reach a certain point (rendezvous) before continuing
 */
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
	ReusableBarrier(int count);
	
};
