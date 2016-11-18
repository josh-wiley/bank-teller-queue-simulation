/**
 *
 * @file ServiceQueueSimulation.cpp
 *
 * @brief Class for simulating a service queue, such as a line of customers
 *        in a bank awaiting service from a teller
 *
 * @author Josh Wiley
 *
 * @details Implements the ServiceQueueSimulation class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef SERVICE_QUEUE_SIMULATION_CPP_
#define SERVICE_QUEUE_SIMULATION_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "ServiceQueueSimulation.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Templated constructor
 *
 * @param[in] queues_ptr
 *            A smart pointer to the list of queues representing customers
 *
 * @param[in] servicers
 *            The number of servicers available to serve the queues of customers
 *
 */
template< class T, class ... V >
ServiceQueueSimulation::ServiceQueueSimulation(
    unsigned int num_servicers,
    std::shared_ptr< std::list< std::shared_ptr< std::list < Customer > > > > events_ptrs,
    T queue_ptr,
    V ... rest_ptrs
)
    : is_complete_(false), current_sim_time_(0), total_line_length_(0),
      max_line_length_(0), line_updates_(0)
{

    // Import pointers to event sources.
    std::for_each(events_ptrs->begin(), events_ptrs->end(), [&, this] (auto ptr)
    {
        // Import.
        arrival_events_.push_back(ptr);
    });

    // Create servicers.
    for (auto i = 0; i < num_servicers; i++)
    {
        // Push new servicer to list.
        servicers_.push_back(Servicer());
    }
    
    // Add queues.
    add_queue(queue_ptr, rest_ptrs...);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes object
 *
 * @param[in] origin
 *            Existing object from which the new object will be instantiated
 *            from
 *
 */
ServiceQueueSimulation::ServiceQueueSimulation(const ServiceQueueSimulation& origin)
    : is_complete_(origin.is_complete_), current_sim_time_(origin.current_sim_time_),
      servicers_(origin.servicers_), customer_queues_(origin.customer_queues_),
      start_time_(origin.start_time_), end_time_(origin.end_time_),
      total_line_length_(origin.total_line_length_),
      max_line_length_(origin.max_line_length_), line_updates_(origin.line_updates_) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
ServiceQueueSimulation::~ServiceQueueSimulation() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating whether or not the simulation has
 *          finished running
 *
 * @return Boolean value indicating whether or not the simulation has finished
 *         running
 *
 */
bool ServiceQueueSimulation::is_complete() const
{
    // Return completion status.
    return is_complete_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns current amount of time since simulation has started running,
 *          or if complete, the total time of the run
 *
 * @return Milliseconds since start of run
 *
 */
unsigned int ServiceQueueSimulation::time_elapsed() const
{
    // Return time elapsed.
    return start_time_.time_since_epoch().count() - end_time_.time_since_epoch().count();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns current amount of simulation (virtual) time has passed in
 *          current simulation
 *
 * @return Elapsed imulation time
 *
 */
unsigned int ServiceQueueSimulation::sim_time() const
{
    // Return elapsed simulation time.
    return current_sim_time_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Calculates and returns average customer wait time
 *
 * @return Average wait time per customer
 *
 */
unsigned int ServiceQueueSimulation::average_customer_wait_time() const 
{
    // Total wait time.
    auto total_wait = (unsigned int) 0;

    // Aggregate.
    return 0;
}
unsigned int ServiceQueueSimulation::max_customer_wait_time() const {}
unsigned int ServiceQueueSimulation::average_line_length() const {}
unsigned int ServiceQueueSimulation::max_line_length() const {}
std::shared_ptr< std::list< unsigned int > > ServiceQueueSimulation::total_servicer_idle_times() const {}
bool ServiceQueueSimulation::waiting_customers() const {}
void ServiceQueueSimulation::process_next_customer() {}
void ServiceQueueSimulation::run() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Variadic templated queue adder to allow for derived classed of base Queue
 *          class
 *
 * @param[in] queue_ptr
 *            Smart pointer to queue to be added
 *
 * @param[in] rest_ptrs
 *            Parameter pack of smart pointers to customer queues
 *
 */
template < class T, class ... V >
void ServiceQueueSimulation::add_queue(T queue_ptr, V ... rest_ptrs)
{
    // Add and recurse (kinda).
    add_queue(queue_ptr);
    add_queue(rest_ptrs...);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Variadic templated queue adder to allow for derived classed of base Queue
 *          class
 *
 * @param[in] queue_ptr
 *            Smart pointer to queue to be added
 *
 */
template < class T >
void ServiceQueueSimulation::add_queue(T queue_ptr)
{
    // Add queue.
    customer_queues_.push_back(queue_ptr);
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICE_QUEUE_SIMULATION_CPP_
//