#Karl Redmond 03/10/2017
#Makefile
#Used to contain commands to compile project
#added -I. to look for any header files with the same .cpp name

EXE = barrierEx
CC = g++
CFLAGS = -std=c++11 -pthread -I.
CFILES = barrierMain.o Semaphore.o

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(CFILES)
	$(CC) $(CFILES) $(CFLAGS) -o $(EXE) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
