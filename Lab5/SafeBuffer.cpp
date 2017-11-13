//   Copyright 2017 Karl Redmond
//   SafeBuffer.cpp
//   Author: Karl Redmond
//   Date:   Thursday,  9 November 2017.
//   License:GNU General Public License v3.0
//   Brief:Class for producer consumer problem, this class is the safe buffer

#include "SafeBuffer.h"
#include <iostream>

/**
   Constructor, spaces provides a fininte buffer size
 */

SafeBuffer::SafeBuffer() {
  items = std::make_shared<Semaphore>(0);
  mutex = std::make_shared<Semaphore>(1);
  spaces = std::make_shared<Semaphore>(100);
}

/**
   Add first checks for available space in the buffer, it then puts a mutex on the queue(safeBuffer) and adds the character. It then releases the mutex and signals items, to indicate that the consumer can take something.
 */

void SafeBuffer::Add(char c) {
  spaces->Wait();
  mutex->Wait();
  safeBuffer.push(c);
  mutex->Signal();
  items->Signal();
}

/**
   Remove first checks if there are items to be consumed, it then claims the mutex and removes an item. Finally it releases the mutex and adds a space to the buffer.
 */

char SafeBuffer::Remove() {
  char c;
  items->Wait();
  mutex->Wait();
  c = safeBuffer.front();
  safeBuffer.pop();
  mutex->Signal();
  spaces->Signal();
  return c;
}
