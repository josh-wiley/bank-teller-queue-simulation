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
#include "QueueList.h"
#include "QueueArray.h"
//
//  Main Function Implementation  //////////////////////////////////////////////
//
int main()
{
  // Data sets.
  auto data_set1_ptr = std::make_shared<std::list<std::pair<unsigned int, unsigned int>>>();
  auto data_set2_ptr = std::make_shared<std::list<std::pair<unsigned int, unsigned int>>>();
  auto data_set3_ptr = std::make_shared<std::list<std::pair<unsigned int, unsigned int>>>();

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

  // Create queues.
  auto queue_list1 = QueueList<std::pair<unsigned int, unsigned int>>(data_set1_ptr);
  auto queue_list2 = QueueList<std::pair<unsigned int, unsigned int>>(data_set2_ptr);
  auto queue_list3 = QueueList<std::pair<unsigned int, unsigned int>>(data_set3_ptr);

  // Log queues.

  // Simulation.

  // Log statistics.

  // Return.
  return 0;
}
#endif // PA05_CPP_
