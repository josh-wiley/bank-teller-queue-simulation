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
#include "../Queue/Queue.h"
#include "../Queue/QueueList.h"
#include "../Queue/QueueArray.h"
#include "Servicer.h"
#include "Customer.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class ServiceQueueSimulation
{

// Public members.
public:
    template<typename T, class ... V>
    ServiceQueueSimulation(
        unsigned int num_servicers,
        std::shared_ptr< std::list< std::shared_ptr< std::list < Customer > > > >,
        T, V...
    ); /**< Parameterized constructor */
    ServiceQueueSimulation(const ServiceQueueSimulation&); /**< Copy constructor */
    ~ServiceQueueSimulation(); /**< Destructor */

    bool is_complete() const; /**< Is the simulation complete? */
    unsigned int time_elapsed() const; /**< Amount of time (ms) that the simulation took to finish, or has been running for */
    unsigned int sim_time() const; /**< Total time units passed in simulation */
    unsigned int average_customer_wait_time() const; /**< Average customer wait time */
    unsigned int max_customer_wait_time() const; /**< Maximum customer wait time */
    unsigned int average_line_length() const; /**< Average length of line */
    unsigned int max_line_length() const; /**< Maximum length of line */
    std::shared_ptr< std::list< unsigned int > > total_servicer_idle_times() const; /**< Total idle times for each servicer */

    bool waiting_customers() const; /**< Returns boolean value indicating if any customers are awaiting service */
    void process_next_customer(); /**< Processes next customer and updates simulation state */
    void run(); /**< Runs simulation until customer queues are empty */

// Private members.
private:
    bool is_complete_; /**< Is the simulation complete? */
    unsigned int current_sim_time_; /**< Amount of time units that have passed in the simulation */
    std::list< Servicer > servicers_; /**< List of servicers */
    std::list< std::shared_ptr< Queue < Customer > > > customer_queues_; /**< List of customer queues */
    std::list< std::shared_ptr< std::list< Customer > > > arrival_events_; /** List of pointers to lists of customer arrival events */
    
    std::chrono::time_point< std::chrono::high_resolution_clock > start_time_; /**< Start time of simulation */
    std::chrono::time_point< std::chrono::high_resolution_clock > end_time_; /**< End time of simulation */
    unsigned int total_line_length_; /**< Total length of line across all simulation updates (used for calculating line averages) */
    unsigned int max_line_length_; /**< Maximum length of line in simulation */
    unsigned int line_updates_; /**< How many line updates occurred in simulation (used for calculating line averages) */

    template < class T, class ... V >
    void add_queue(T, V...); /**< Variadic template to add queue and recurse (kinda) */
    
    template < class T >
    void add_queue(T); /**< Variadic template to add queue */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICE_QUEUE_SIMULATION_H_
//