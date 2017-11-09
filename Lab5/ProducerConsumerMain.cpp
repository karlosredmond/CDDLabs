/* Copyright 2017 Karl Redmond
   ProducerConsumerMain.cpp
   Author: Karl Redmond 
   Date:   Thursday,  9 November 2017.
   License:GNU General Public License v3.0
   Brief:Producer consumer main*/

#include "SafeBuffer.h"
#include <iostream>
#include <chrono>
#include <thread>

int characterCountBuffer[26] = {0};

char generateRandomCharacter() {
  int n = std::rand() % 26;
  char c = n + 97;
  return c;
}

void ConsumerMethod(std::shared_ptr<SafeBuffer> sBuff) {
  char c;
  do {
    c = sBuff->Consumer();
    characterCountBuffer[c - 97]++;
  } while ( c != 'X');
}

void ProducerMethod(std::shared_ptr<SafeBuffer> sBuff) {
  char c;
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
    c = generateRandomCharacter();
    sBuff->Producer(c);
  } while ( c != 'X' );
}

int main(void) {
  const int sizeOfBuffer = 1000;
  int numCharacters;
  std::shared_ptr<SafeBuffer> sBuff(new SafeBuffer);
  std::thread producerThread;
  std::thread consumerThread;

  std::cout << "How many characters do we add?" << std::endl;
  std::cin >> numCharacters;

  producerThread = std::thread(ProducerMethod, sBuff);
  consumerThread = std::thread(ConsumerMethod, sBuff);
  producerThread.join();
  consumerThread.join();
  /**< Launch the threads  */
                                    /*  for ( int i = 0; i < numThreads; i++ ) {
    threadArr[i] = std::thread(taskOne, rb);
  }
  for ( int i =0; i <numThreads; i++ ) {
    threadArr[i].join();
    }*/
  std::cout << "All Threads Finished, back in main"<< std::endl;
  return 0;
}
