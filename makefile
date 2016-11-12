# Variables.
CC = g++
STD = -std=c++14
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o PA05


# Executable.
PA05: PA05.o data_generator.o sorter.o QueueList.o QueueArray.o
	$(CC) $(STD) $(LFLAGS) PA05.o data_generator.o sorter.o QueueList.o QueueArray.o $(OFLAGS)


# PA05.
PA05.o: PA05.cpp data_generator.h sorter.h
	$(CC) $(STD) $(CFLAGS) PA05.cpp


# Data generator.
data_generator.o: data_generator.h data_generator.cpp
	$(CC) $(STD) $(CFLAGS) data_generator.cpp


# Sorter.
sorter.o: sorter.h sorter.cpp
	$(CC) $(STD) $(CFLAGS) sorter.cpp


# Queue (list implementation).
QueueList.o: QueueList.h QueueList.cpp
	$(CC) $(STD) $(CFLAGS) QueueList.cpp


# Queue (array implementation).
QueueArray.o: QueueArray.h QueueArray.cpp
	$(CC) $(STD) $(CFLAGS) QueueArray.cpp


# Clean.
clean:
	rm -rf *.o PA05 input.txt results.txt
