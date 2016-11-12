/**
 *
 * @file PA05.cpp
 *
 * @brief Driver event-driven simulation of bank teller queue.
 *
 * @author Josh Wiley
 *
 * @details Generates random data, sorts it by arrial time, and processes in a
 *          manner to simulate the behavior fo a bank teller queue.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef PA05_CPP_
#define PA05_CPP_
#define NUM_EVENTS (unsigned int) 99999
#define MIN_START_TIME (unsigned int) 0
#define MAX_START_TIME (unsigned int) 100000
#define MIN_TRANSACTION_TIME (unsigned int) 0
#define MAX_TRANSACTION_TIME (unsigned int) 100
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <iostream>
#include <memory>
#include <list>
#include <utility>
#include <algorithm>
#include "data_generator.h"
#include "sorter.h"
#include "Queue.h"
#include "QueueList.h"
#include "QueueArray.h"
#include "Logger.h"
#include "ServiceQueueSimulation.h"
//
//  Main Function Implementation  //////////////////////////////////////////////
//
int main()
{
  // Checkpoint.
  std::cout << "\n\nGenerating random data set...\n" << std::endl;

  // Data sets.
  auto data_set1_ptr = std::shared_ptr< std::list< std::pair< unsigned int, unsigned int > > >(
    new std::list< std::pair< unsigned int, unsigned int > >()
  );
  auto data_set2_ptr = std::shared_ptr< std::list< std::pair< unsigned int, unsigned int > > >(
    new std::list< std::pair< unsigned int, unsigned int > >()
  );
  auto data_set3_ptr = std::shared_ptr< std::list< std::pair< unsigned int, unsigned int > > >(
    new std::list< std::pair< unsigned int, unsigned int > >()
  );

  // Loggers.
  auto data_logger = Logger("data.txt");
  auto stats_logger = Logger("results.txt");

  // Generate random data for data set #1.
  data_generator::generateRandomData(
    NUM_EVENTS,
    MIN_START_TIME,
    MAX_START_TIME,
    MIN_TRANSACTION_TIME,
    MAX_TRANSACTION_TIME,
    data_set1_ptr
  );

  // Generate random data for data set #2.
  data_generator::generateRandomData(
    NUM_EVENTS,
    MIN_START_TIME,
    MAX_START_TIME,
    MIN_TRANSACTION_TIME,
    MAX_TRANSACTION_TIME,
    data_set2_ptr
  );

  // Generate random data for data set #3.
  data_generator::generateRandomData(
    NUM_EVENTS,
    MIN_START_TIME,
    MAX_START_TIME,
    MIN_TRANSACTION_TIME,
    MAX_TRANSACTION_TIME,
    data_set3_ptr
  );

  // Checkpoint.
  std::cout << "\n\nSorting data set by start time...\n" << std::endl;

  // Sort data set #1.
  sorter::counting_sort(
    data_set1_ptr->begin(),
    data_set1_ptr->end(),
    MIN_START_TIME,
    MAX_START_TIME
  );

  // Sort data set #2.
  sorter::counting_sort(
    data_set2_ptr->begin(),
    data_set2_ptr->end(),
    MIN_START_TIME,
    MAX_START_TIME
  );

  // Sort data set #3.
  sorter::counting_sort(
    data_set3_ptr->begin(),
    data_set3_ptr->end(),
    MIN_START_TIME,
    MAX_START_TIME
  );

  // Checkpoint.
  std::cout << "\n\nLogging data sets...\n" << std::endl;

  // Log data sets.
  data_logger.log_pair_list("Data set #1", data_set1_ptr);
  data_logger.log_pair_list("Data set #2", data_set2_ptr);
  data_logger.log_pair_list("Data set #3", data_set3_ptr);

  // Checkpoint.
  std::cout << "\n\nCreating queues...\n" << std::endl;

  // Create queues.
  auto queue_list1 = QueueList< std::pair<unsigned int, unsigned int> >(data_set1_ptr);
  auto queue_list2 = QueueList< std::pair<unsigned int, unsigned int> >(data_set2_ptr);
  auto queue_list3 = QueueList< std::pair<unsigned int, unsigned int> >(data_set3_ptr);
  auto queue_array1 = QueueArray< std::pair<unsigned int, unsigned int> >(NUM_EVENTS, data_set1_ptr);
  auto queue_array2 = QueueArray< std::pair<unsigned int, unsigned int> >(NUM_EVENTS, data_set2_ptr);
  auto queue_array3 = QueueArray< std::pair<unsigned int, unsigned int> >(NUM_EVENTS, data_set3_ptr);

  // Build lists of queues.
  auto sim1_queues = std::list<Queue < std::pair< unsigned int, unsigned int > > >();
  auto sim2_queue = std::list<Queue < std::pair< unsigned int, unsigned int > > >();
  auto sim3_queue = std::list<Queue < std::pair< unsigned int, unsigned int > > >();

  // Simulations.

  // Log statistics.

  // Checkpoint.
  std::cout << "\n\nSuccess!\n\n" << std::endl;

  // Return.
  return 0;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // PA05_CPP_
//