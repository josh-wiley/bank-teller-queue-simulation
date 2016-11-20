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
#include <chrono>
#include <algorithm>
#include "../Queue/Queue.h"
#include "../Queue/QueueList.h"
#include "../Queue/QueueArray.h"
#include "Servicer.h"
#include "Customer.h"
#include <iostream> // TODO: REMOVE
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class ServiceQueueSimulation
{

// Public members.
public:
    template<class T, class ... V>
    ServiceQueueSimulation(
        unsigned int num_servicers,
        std::shared_ptr< std::list < Customer > >,
        T, V...
    ); /**< Parameterized constructor */
    ServiceQueueSimulation(const ServiceQueueSimulation&); /**< Copy constructor */
    ~ServiceQueueSimulation(); /**< Destructor */

    bool is_complete() const; /**< Is the simulation complete? */
    unsigned int time_elapsed() const; /**< Amount of time (ms) that the simulation took to finish, or has been running for */
    unsigned int sim_time() const; /**< Total time units passed in simulation */
    float average_customer_wait_time() const; /**< Average customer wait time */
    unsigned int max_customer_wait_time() const; /**< Maximum customer wait time */
    float average_line_length() const; /**< Average length of line */
    unsigned int max_line_length() const; /**< Maximum length of line */
    std::shared_ptr< std::list< unsigned int > > total_servicer_idle_times() const; /**< Total idle times for each servicer */

    void run(); /**< Runs simulation until customer queues are empty */

// Private members.
private:
    bool is_complete_; /**< Is the simulation complete? */
    unsigned int current_sim_time_; /**< Amount of time units that have passed in the simulation */
    std::list< std::shared_ptr< Servicer > > servicers_; /**< List of servicers */
    std::list< std::shared_ptr< Queue < std::shared_ptr< Customer > > > > customer_queues_; /**< List of customer queues */
    std::list< std::shared_ptr< Customer > > customer_events_; /** List of pointers to lists of customer arrival events */

    std::chrono::time_point< std::chrono::high_resolution_clock > start_time_; /**< Start time of simulation */
    std::chrono::time_point< std::chrono::high_resolution_clock > end_time_; /**< End time of simulation */
    unsigned int max_line_length_; /**< Max line length during simulation */
    unsigned int total_line_length_; /**< Total length of line across all simulation updates (used for calculating line averages) */
    unsigned int line_updates_; /**< How many line updates occurred in simulation (used for calculating line averages) */

    std::shared_ptr< Queue < std::shared_ptr< Customer > > > shortest_queue() const; /**< Return pointer to shortest queue */
    bool all_servicers_idle() const; /**< Return boolean value indicating if all servicers are idle. */
    unsigned int get_next_departure_time() const; /**< Returns next customer departure time */
    bool is_waiting_customers(std::shared_ptr< Customer >&) const; /**< Returns boolean value indicating if customers are waiting in the queue, and returns a pointer to the customer who has been waiting the longest */
    bool is_servicer_available(std::shared_ptr< Servicer >&) const; /**< Returns boolean value indicating if servicers are available, and returns a pointer the first available servicer via out parameter */

    template < class T, class ... V >
    void add_queue(T, V...); /**< Variadic template to add queue and recurse (kinda) */

    template < class T >
    void add_queue(T); /**< Variadic template to add queue */

};
//
//  Implementation Files  //////////////////////////////////////////////////////
//
#include "ServiceQueueSimulation.cpp"
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICE_QUEUE_SIMULATION_H_
//
