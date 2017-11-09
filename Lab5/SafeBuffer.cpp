//   Copyright 2017 Karl Redmond
//   SafeBuffer.cpp
//   Author: Karl Redmond
//   Date:   Thursday,  9 November 2017.
//   License:GNU General Public License v3.0
//   Brief:Class for producer consumer problem, this class is the safe buffer

#include "SafeBuffer.h"
#include <iostream>

SafeBuffer::SafeBuffer() {
  items = std::make_shared<Semaphore>(0);
  mutex = std::make_shared<Semaphore>(0);
  spaces = std::make_shared<Semaphore>(1000);
}

void SafeBuffer::Producer(char c) {
  spaces->Wait();
  mutex->Wait();
    safeBuffer.push(c);
  mutex->Signal();
  items->Signal();
}

char SafeBuffer::Consumer() {
  char c;
  items->Wait();
  mutex->Wait();
  c = safeBuffer.front();
  safeBuffer.pop();
  mutex->Signal();
  items->Signal();
  return c;
}
