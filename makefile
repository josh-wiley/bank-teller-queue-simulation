# Variables.
CC = g++
STD = -std=c++14
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o PA05


# Executable.
PA05: PA05.o data_generator.o sorter.o Logger.o ServiceQueueSimulation.o
	$(CC) $(STD) $(LFLAGS) PA05.o data_generator.o sorter.o Logger.o ServiceQueueSimulation.o $(OFLAGS)


# PA05.
PA05.o: PA05.cpp data_generator.h sorter.h Logger.h QueueList.h QueueArray.h ServiceQueueSimulation.h
	$(CC) $(STD) $(CFLAGS) PA05.cpp


# Data generator.
data_generator.o: data_generator.h data_generator.cpp
	$(CC) $(STD) $(CFLAGS) data_generator.cpp


# Sorter.
sorter.o: sorter.h sorter.cpp
	$(CC) $(STD) $(CFLAGS) sorter.cpp


# Logger.
Logger.o: Logger.h Logger.cpp
	$(CC) $(STD) $(CFLAGS) Logger.cpp


# Service queue simulation.
ServiceQueueSimulation.o: ServiceQueueSimulation.h ServiceQueueSimulation.cpp Queue.h
	$(CC) $(STD) $(CFLAGS) ServiceQueueSimulation.cpp


# Clean.
clean:
	rm -rf *.o PA05 data.txt results.txt
