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
#define NUM_TELLERS_SIM_1 (unsigned int) 1
#define NUM_TELLERS_SIM_2 (unsigned int) 3
#define NUM_TELLERS_SIM_3 (unsigned int) 3
#define NUM_TELLERS_SIM_4 (unsigned int) 8
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <iostream>
#include <memory>
#include <list>
#include <chrono>
#include "utils/data_generator.h"
#include "utils/sorter.h"
#include "Queue/Queue.h"
#include "Queue/QueueList.h"
#include "Queue/QueueArray.h"
#include "Logger/Logger.h"
#include "ServiceQueueSimulation/Customer.h"
#include "ServiceQueueSimulation/ServiceQueueSimulation.h"
//
//  Main Function Implementation  //////////////////////////////////////////////
//
int main()
{
  // Checkpoint.
  std::cout << "\n\nGenerating random data set...\n" << std::endl;

  // Data sets.
  auto data_set1_ptr = std::shared_ptr< std::list< Customer > >(
    new std::list< Customer >()
  );
  auto data_set2_ptr = std::shared_ptr< std::list< Customer > >(
    new std::list< Customer >()
  );
  auto data_set3_ptr = std::shared_ptr< std::list< Customer > >(
    new std::list< Customer >()
  );

  // Loggers.
  auto data_logger = Logger("data.txt");
  auto stats_logger = Logger("results.txt");

  // Generate random data for data set #1.
  data_generator::generate_random_data(
    NUM_EVENTS,
    MIN_START_TIME,
    MAX_START_TIME,
    MIN_TRANSACTION_TIME,
    MAX_TRANSACTION_TIME,
    data_set1_ptr
  );

  // Generate random data for data set #2.
  data_generator::generate_random_data(
    NUM_EVENTS,
    MIN_START_TIME,
    MAX_START_TIME,
    MIN_TRANSACTION_TIME,
    MAX_TRANSACTION_TIME,
    data_set2_ptr
  );

  // Generate random data for data set #3.
  data_generator::generate_random_data(
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
  sorter::counting_sort_by_arrival_time(
    data_set1_ptr->begin(),
    data_set1_ptr->end(),
    MIN_START_TIME,
    MAX_START_TIME
  );

  // Sort data set #2.
  sorter::counting_sort_by_arrival_time(
    data_set2_ptr->begin(),
    data_set2_ptr->end(),
    MIN_START_TIME,
    MAX_START_TIME
  );

  // Sort data set #3.
  sorter::counting_sort_by_arrival_time(
    data_set3_ptr->begin(),
    data_set3_ptr->end(),
    MIN_START_TIME,
    MAX_START_TIME
  );

  // Checkpoint.
  std::cout << "\n\nLogging data sets...\n" << std::endl;

  // Log data sets.
  data_logger.log_customer_list("Data set #1", data_set1_ptr);
  data_logger.log_customer_list("Data set #2", data_set2_ptr);
  data_logger.log_customer_list("Data set #3", data_set3_ptr);

  // Checkpoint.
  std::cout << "\n\nCreating queues...\n" << std::endl;

  // Customer queues.
  auto queue_list1 = QueueList< Customer >(data_set1_ptr);
  auto queue_list2 = QueueList< Customer >(data_set2_ptr);
  auto queue_list3 = QueueList< Customer >(data_set3_ptr);
  auto queue_array1 = QueueArray< Customer >(NUM_EVENTS, data_set1_ptr);
  auto queue_array2 = QueueArray< Customer >(NUM_EVENTS, data_set2_ptr);
  auto queue_array3 = QueueArray< Customer >(NUM_EVENTS, data_set3_ptr);

  // Pointers to list of customer queue pointers.
  auto sim1_list_queues_ptr = std::shared_ptr< std::list< Queue < Customer >* > >();
  auto sim2_mixed_queues_ptr = std::shared_ptr< std::list< Queue < Customer >* > >();
  auto sim3_array_queues_ptr = std::shared_ptr< std::list< Queue < Customer >* > >();
  auto sim4_mixed_queues_ptr = std::shared_ptr< std::list< Queue < Customer >* > >();

  // Add customer queue pointer to simulation #1 queue list.
  sim1_list_queues_ptr->push_back(&queue_list1);

  // Add customer queue pointers to simulation #2 queues list.
  sim2_mixed_queues_ptr->push_back(&queue_array1);
  sim2_mixed_queues_ptr->push_back(&queue_list2);
  sim2_mixed_queues_ptr->push_back(&queue_array3);

  // Add customer queue pointer to simulation #3 queues list.
  sim3_array_queues_ptr->push_back(&queue_array1);

  // Add queue pointers to simulation #4 queues list.
  sim4_mixed_queues_ptr->push_back(&queue_list1);
  sim4_mixed_queues_ptr->push_back(&queue_array1);
  sim4_mixed_queues_ptr->push_back(&queue_list2);
  sim4_mixed_queues_ptr->push_back(&queue_array2);
  sim4_mixed_queues_ptr->push_back(&queue_list3);
  sim4_mixed_queues_ptr->push_back(&queue_array3);

  // Simulations.
  auto sim1 = ServiceQueueSimulation(sim1_list_queues_ptr, NUM_TELLERS_SIM_1);
  auto sim2 = ServiceQueueSimulation(sim2_mixed_queues_ptr, NUM_TELLERS_SIM_2);
  auto sim3 = ServiceQueueSimulation(sim3_array_queues_ptr, NUM_TELLERS_SIM_2);
  auto sim4 = ServiceQueueSimulation(sim4_mixed_queues_ptr, NUM_TELLERS_SIM_4);

  // Run simulations.
  sim1.run();
  sim2.run();
  sim3.run();
  sim4.run();

  // Log statistics.
  stats_logger.log_sim_results(
    "Simulation #1 (link-based queue)",
    std::make_shared< ServiceQueueSimulation >(sim1)
  );
  stats_logger.log_sim_results(
    "Simulation #2 (array-based and link-based queues)",
    std::make_shared< ServiceQueueSimulation >(sim2)
  );
  stats_logger.log_sim_results(
    "Simulation #3 (array-based queue)",
    std::make_shared< ServiceQueueSimulation >(sim3)
  );
  stats_logger.log_sim_results(
    "Simulation #4 (array-based and link-based queues)",
    std::make_shared< ServiceQueueSimulation >(sim4)
  );

  // Checkpoint.
  std::cout << "\n\nSuccess! Simulation results have been logged.\n\n" << std::endl;

  // Return.
  return 0;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // PA05_CPP_
//