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
  std::cout << "\n\nCreating simulations...\n" << std::endl;


  // Simulations.
  auto sim1 = ServiceQueueSimulation(
    NUM_TELLERS_SIM_1,
    data_set1_ptr,
    std::shared_ptr< QueueArray< Customer > >()
  );
  auto sim2 = ServiceQueueSimulation(
    NUM_TELLERS_SIM_2,
    data_set2_ptr,
    std::shared_ptr<QueueArray< Customer > >(),
    std::shared_ptr< QueueList< Customer > >(),
    std::shared_ptr< QueueArray< Customer > >()
  );
  auto sim3 = ServiceQueueSimulation(
    NUM_TELLERS_SIM_3,
    data_set3_ptr,
    std::shared_ptr< QueueList< Customer > >(),
    std::shared_ptr< QueueArray< Customer > >(),
    std::shared_ptr< QueueList< Customer > >()
  );
  auto sim4 = ServiceQueueSimulation(
    NUM_TELLERS_SIM_4,
    data_set1_ptr,
    std::shared_ptr< QueueArray< Customer > >(),
    std::shared_ptr< QueueList< Customer > >()
  );


  // Checkpoint.
  std::cout << "\n\nRunning simulations...\n" << std::endl;


  // Run simulations.
  sim1.run();
  sim2.run();
  sim3.run();
  sim4.run();


  // Checkpoint.
  std::cout << "\n\nLogging results...\n" << std::endl;


  // Log statistics.
  stats_logger.log_sim_results(
    "Simulation #1 (link-based queue)",
    std::shared_ptr< ServiceQueueSimulation >(new ServiceQueueSimulation(sim1))
  );
  stats_logger.log_sim_results(
    "Simulation #2 (array-based and link-based queues)",
    std::shared_ptr< ServiceQueueSimulation >(new ServiceQueueSimulation(sim2))
  );
  stats_logger.log_sim_results(
    "Simulation #3 (array-based queue)",
    std::shared_ptr< ServiceQueueSimulation >( new ServiceQueueSimulation(sim3))
  );
  stats_logger.log_sim_results(
    "Simulation #4 (array-based and link-based queues)",
    std::shared_ptr< ServiceQueueSimulation >(new ServiceQueueSimulation(sim4))
  );

  // Return.
  return 0;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // PA05_CPP_
//