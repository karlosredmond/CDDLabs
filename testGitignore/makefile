#Karl Redmond 03/10/2017
#Makefile
#Used to contain commands to compile project
#added -I. to look for any header files with the same .cpp name

EXE = signal
CC = g++
CFLAGS = -std=c++11 -pthread -I.
CFILES = signal.o Semaphore.o

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

ALL: $(CFILES)
	$(CC) $(CFILES) $(CFLAGS) -o $(EXE)


#this is customary and just deletes all .o files


CLEAN:
	rm *.o
