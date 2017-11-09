#ifndef SAFEBUFFER_H
#define SAFEBUFFER_H

/* Copyright 2017 Karl Redmond
   SafeBuffer.hAuthor: Karl Redmond 
   Date:   Thursday,  9 November 2017.
   License:GNU General Public License v3.0
   Brief:Header File for SafeBuffer*/

#include <mutex>
#include "Semaphore.h"
#include <queue>

/*!  Class used to provide safe access to a shared buffer.*/

class SafeBuffer {
  std::shared_ptr<Semaphore> mutex;
  std::shared_ptr<Semaphore> items;
  std::shared_ptr<Semaphore> spaces;
  std::queue<char> safeBuffer;
  int maxChars;

 public:
  SafeBuffer();
  void Producer(char);
  char Consumer();
};

#endif //  SAFEBUFFER_H_
