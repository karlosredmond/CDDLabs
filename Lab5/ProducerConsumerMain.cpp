/* Copyright 2017 Karl Redmond
   ProducerConsumerMain.cpp
   Author: Karl Redmond 
   Date:   Thursday,  9 November 2017.
   License:GNU General Public License v3.0
   Brief:Producer consumer main uses SafeBuffer to demonstrate a number of threads that are sharing a buffer. N threads will produce, and M threads will consume.*/

#include "SafeBuffer.h"
#include <iostream>
#include <chrono>
#include <thread>

/**
   Central Buffer for storing count of characters.
 */
int characterCountBuffer[26] = {0};

/**
   ConsumerMethod removes a character from the safe buffer, at random time intevals. It also keeps track of the count of each letter removed.
 */

void ConsumerMethod(std::shared_ptr<SafeBuffer> sBuff) {
  char c;
  do {
    c = sBuff->Remove();
    std::cout << "Consuming " << c << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
    characterCountBuffer[c]++;
  } while ( c != 'X');
}

/**
   ProducerMethod adds a random character to a safe buffer, at random timer intervals. 
 */

void ProducerMethod(std::shared_ptr<SafeBuffer> sBuff, int numCharacters) {
  char c;
  int i = 0;
  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
    c =  std::rand() % 26 + 97;
    if ( ++i == numCharacters ) {
      c = 'X';
    }
    sBuff->Add(c);
    std::cout << "Producing " << c << std::endl;
  } while ( c != 'X' );
}

/**
   PrintArray prints the count of each letter consumed: a 10...
 */

void PrintArray() {
  for ( char i = 97; i < 123; ++i ) {
    std::cout << i << " " << characterCountBuffer[i] << std::endl;
  }
}

int main(void) {
  int numCharacters;
  std::shared_ptr<SafeBuffer> sBuff(new SafeBuffer);
  std::thread producerThread[10];
  std::thread consumerThread[10];

  std::cout << "How many characters do we add?" << std::endl;
  std::cin >> numCharacters;

  for ( int i = 0; i < 10; i++ ) {
    producerThread[i] = std::thread(ProducerMethod, sBuff, numCharacters);
    consumerThread[i] = std::thread(ConsumerMethod, sBuff);
  }

  for ( int i = 0; i < 10; ++i ) {
    producerThread[i].join();
    consumerThread[i].join();
  }

  PrintArray();
  std::cout << "All Threads Finished, back in main"<< std::endl;
  return 0;
}
