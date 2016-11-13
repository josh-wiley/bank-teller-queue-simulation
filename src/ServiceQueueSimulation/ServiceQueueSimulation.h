/**
 *
 * @file ServiceQueueSimulation.h
 *
 * @brief Class for simulating a service queue, such as a line of customers
 *        in a bank awaiting service from a teller
 *
 * @author Josh Wiley
 *
 * @details Defines the ServiceQueueSimulation class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef SERVICE_QUEUE_SIMULATION_H_
#define SERVICE_QUEUE_SIMULATION_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <memory>
#include <list>
#include <iterator>
#include <utility>
#include <chrono>
#include "../Queue/Queue.h"
#include "Servicer.h"
#include "Customer.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class ServiceQueueSimulation
{

// Public members.
public:
    ServiceQueueSimulation(
        std::shared_ptr< std::list<Queue < std::pair< unsigned int, unsigned int > > > >,
        unsigned int servicers = 1); /**< Parameterized constructor */
    ServiceQueueSimulation(const ServiceQueueSimulation&); /**< Copy constructor */
    ~ServiceQueueSimulation(); /**< Destructor */

    bool waiting_customers() const; /**< Returns boolean value indicating if any customers are awaiting service */
    void process_next_customer(); /**< Processes next customer and updates simulation state */
    void run(); /**< Runs simulation until customer queues are empty */
    std::chrono::milliseconds time_elapsed() const; /**< Amount of time that the simulation took to finish, or has been running for */

// Private members.
private:
    std::chrono::time_point< std::chrono::high_resolution_clock, std::chrono::milliseconds > start_time_; /**< Start time of simulation */
    std::chrono::time_point< std::chrono::high_resolution_clock, std::chrono::milliseconds > end_time_; /**< End time of simulation */
    unsigned int current_sim_time_; /**< Amount of time units that have passed in the simulation */
    std::list< Servicer > servicers_; /**< List of servicers */
    std::list< Queue < Customer > > customer_queues_; /**< List of customers */
    std::list< Queue < Customer > >::iterator next_customer_it_; /**< Iterator pointing to next customer to receive serviced */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICE_QUEUE_SIMULATION_H_
//