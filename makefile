# Variables.
CC = g++
STD = -std=c++14
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o PA05


# Executable.
PA05: PA05.o data_generator.o sorter.o Customer.o Servicer.o
	$(CC) $(STD) $(LFLAGS) PA05.o data_generator.o sorter.o Customer.o Servicer.o $(OFLAGS)


# PA05.
PA05.o: src/PA05.cpp src/utils/data_generator.h src/utils/sorter.h src/Logger/Logger.h src/Queue/QueueList.h src/Queue/QueueArray.h src/ServiceQueueSimulation/ServiceQueueSimulation.h
	$(CC) $(STD) $(CFLAGS) src/PA05.cpp


# Data generator.
data_generator.o: src/utils/data_generator.h src/utils/data_generator.cpp src/ServiceQueueSimulation/Customer.h
	$(CC) $(STD) $(CFLAGS) src/utils/data_generator.cpp


# Sorter.
sorter.o: src/utils/sorter.h src/utils/sorter.cpp
	$(CC) $(STD) $(CFLAGS) src/utils/sorter.cpp


# Customer.
Customer.o: src/ServiceQueueSimulation/Customer.h src/ServiceQueueSimulation/Customer.cpp
	$(CC) $(STD) $(CFLAGS) src/ServiceQueueSimulation/Customer.cpp


# Servicer.
Servicer.o: src/ServiceQueueSimulation/Servicer.h src/ServiceQueueSimulation/Servicer.cpp src/ServiceQueueSimulation/Customer.h
	$(CC) $(STD) $(CFLAGS) src/ServiceQueueSimulation/Servicer.cpp


# Clean.
clean:
	rm -rf *.o PA05 data.txt results.txt
