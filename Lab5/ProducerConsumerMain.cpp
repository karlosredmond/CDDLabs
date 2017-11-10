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
#include <ctime>
#include <random>

int characterCountBuffer[26] = {0};

void ConsumerMethod(std::shared_ptr<SafeBuffer> sBuff) {
  char c;
  do {
    c = sBuff->Remove();
    std::cout << "Consuming " << c << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
    characterCountBuffer[c]++;
  } while ( c != 'X');
}

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

  for ( char i = 97; i < 123; ++i ) {
    std::cout << i << " " << characterCountBuffer[i] << std::endl;
  }

  std::cout << "All Threads Finished, back in main"<< std::endl;
  return 0;
}
