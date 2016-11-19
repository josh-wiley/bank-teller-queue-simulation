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
    std::shared_ptr< std::list < Customer > > events_ptr,
    T queue_ptr,
    V ... rest_ptrs
)
    : is_complete_(false), current_sim_time_(0), max_line_length_(0),
      total_line_length_(0), line_updates_(0)
{

    // Copy events from source.
    customer_events_ = std::list< Customer >(*events_ptr);

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
      customer_events_(origin.customer_events_), start_time_(origin.start_time_),
      end_time_(origin.end_time_), max_line_length_(origin.max_line_length_),
      total_line_length_(origin.total_line_length_), line_updates_(origin.line_updates_) {}
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
float ServiceQueueSimulation::average_customer_wait_time() const 
{
    // Total wait time.
    auto total_wait_ptr = std::shared_ptr< unsigned int >(0);
    auto total_events_ptr = std::shared_ptr< unsigned int >(0);

    // Each events list.
    std::for_each(customer_events_.begin(), customer_events_.end(), [total_wait_ptr, total_events_ptr] (auto event)
    {
        // Wait time.
        *total_wait_ptr += event.departure_time() - event.transaction_length() - event.arrival_time();

        // Total.
        (*total_events_ptr)++;
    });

    // Return.
    return *total_wait_ptr / *total_events_ptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Computes and returns max customer wait time
 *
 * @return Max wait time per customer
 *
 */
unsigned int ServiceQueueSimulation::max_customer_wait_time() const
{
    // Max wait time.
    auto max_wait_ptr = std::shared_ptr< unsigned int >(0);
    auto current_wait_ptr = std::shared_ptr< unsigned int >(0);

    // Each events list.
    std::for_each(customer_events_.begin(), customer_events_.end(), [max_wait_ptr, current_wait_ptr] (auto event)
    {
        // Get wait time.
        *current_wait_ptr = event.departure_time() - event.transaction_length() - event.arrival_time();

        // Is new max?
        if (*current_wait_ptr > *max_wait_ptr)
        {
            // Assign new max.
            *max_wait_ptr = *current_wait_ptr;
        }
    });

    // Return max.
    return *max_wait_ptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Computes and returns average line length
 *
 * @return Average line length of simulation
 *
 */
float ServiceQueueSimulation::average_line_length() const
{
    // Return average.
    return line_updates_ / total_line_length_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns max line length
 *
 * @return Max line length of simulation
 *
 */
unsigned int ServiceQueueSimulation::max_line_length() const
{
    // Return max.
    return max_line_length_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns smart pointer to a list of idle times for each servicer
 *
 * @return Smart pointer to a list of idle times for each servicer
 *
 */
std::shared_ptr< std::list< unsigned int > > ServiceQueueSimulation::total_servicer_idle_times() const
{
    // Save list.
    auto totals_list_ptr = std::shared_ptr< std::list< unsigned int > >( new std::list< unsigned int >());

    // Add totals.
    std::for_each(servicers_.begin(), servicers_.end(), [totals_list_ptr] (auto servicer)
    {
        // Add idle time.
        totals_list_ptr->push_back(servicer.total_idle_time());
    });

    // Return.
    return totals_list_ptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Runs the simulation until the end
 *
 */
void ServiceQueueSimulation::run()
{
    // Event iterators.
    auto next_arrival_it = customer_events_.begin();
    auto end_it = customer_events_.end();
    
    // Cached results.
    auto next_arrival_time = next_arrival_it->arrival_time();
    auto next_customer_departure_time = (unsigned int) 0;

    // Pointer to an available servicer.
    auto servicer_ptr = std::shared_ptr< Servicer >();
    auto customer_ptr = std::shared_ptr< Customer>();

    // Events to process?
    while (next_arrival_it != end_it || all_servicers_idle())
    {
        // Arrival?
        if (next_arrival_it != end_it && next_customer_departure_time <= next_arrival_time)
        {
            // Advance time to next departure.
            current_sim_time_ = next_arrival_time;

            // Enqueue.
            shortest_queue()->enqueue(std::make_shared< Customer >(*next_arrival_it));

            // Advance iterator.
            ++next_arrival_it;

            // Cache new arrival time.
            next_arrival_time = next_arrival_it->arrival_time();
        }
        // Fast-forward to next departure.
        else
        {
            // Advance time to next departure.
            current_sim_time_ = next_customer_departure_time;

            // Advance next departure time.
            next_customer_departure_time = next_departure_time();
        }

        // Are waiting customers and servicers available?
        while (is_waiting_customers() && is_servicer_available(servicer_ptr)) {
            // Get next customer from queue.
            customer_ptr = next_customer_to_be_serviced();

            // Service customer.
            servicer_ptr->service_customer(current_sim_time_, customer_ptr);
        }
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns pointer to shortest queue
 *
 * @return Smart pointer to shortest queue
 *
 */
std::shared_ptr< Queue < std::shared_ptr< Customer > > > ServiceQueueSimulation::shortest_queue() const
{
    // Pointer to shortest queue, cursor, and end.
    auto shortest_queue_ptr_it = customer_queues_.begin();
    auto cursor_it = next(shortest_queue_ptr_it);
    auto end_it = customer_queues_.end();


    // Each other queue.
    while(cursor_it != end_it)
    {
        // Shorter than current shortest?
        if ((*shortest_queue_ptr_it)->size() > (*cursor_it)->size())
        {
            // Assign new shortest queue.
            shortest_queue_ptr_it = cursor_it;
        }

        // Advance.
        ++cursor_it;
    }

    // Return.
    return *shortest_queue_ptr_it;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if all servicers are idle
 *
 * @return Boolean value indicating if all servicers are idle
 *
 */
bool ServiceQueueSimulation::all_servicers_idle() const
{
    // Servicer iterators.
    auto cursor_it = servicers_.begin();
    auto end_it = servicers_.end();

    // Check each servicer.
    while (cursor_it != end_it)
    {
        // Check.
        if (cursor_it->available(current_sim_time_))
        {
            // Return.
            return false;
        }

        // Advance.
        ++cursor_it;
    }

    // Return.
    return true;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a number indicating the time of the next departure event
 *
 * @return Unsigned integer indicating the time of the next departure event
 *
 */
unsigned int ServiceQueueSimulation::next_departure_time() const
{
    // Servicer iterators.
    auto s_cursor_it = servicers_.begin();
    auto s_end_it = servicers_.end();

    // Next departure time.
    auto departure_times = std::list< unsigned int >();

    // Check each servicer.
    while (s_cursor_it != s_end_it)
    {
        // Check.
        if (!s_cursor_it->available(current_sim_time_))
        {
            // Get departure time.
            departure_times.push_back(s_cursor_it->unavailable_until());
        }

        // Advance.
        ++s_cursor_it;
    }

    // Are all servicers available?
    if (departure_times.empty())
    {
        // Return 0.
        return 0;
    }

    // Get departure time iterators.
    auto dt_cursor_it = departure_times.begin();
    auto dt_end_it = departure_times.end();

    // Get first value and advance cursor.
    auto next_departure_time = *dt_cursor_it;
    ++dt_cursor_it;

    // Find smallest.
    while (dt_cursor_it != dt_end_it)
    {
        // Check.
        if (*dt_cursor_it < next_departure_time)
        {
            // New next departure time.
            next_departure_time = *dt_cursor_it;
        }

        // Advance.
        ++dt_cursor_it;
    }

    // Return.
    return next_departure_time;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if there are any customers
 *          waiting for service
 *
 * @return Boolean value indicating if there are any customers waiting for
 *         service
 *
 */
bool ServiceQueueSimulation::is_waiting_customers() const
{
    // Get queue iterators.
    auto cursor_it = customer_queues_.begin();
    auto end_it = customer_queues_.end();

    // Check each.
    while (cursor_it != end_it)
    {
        // Not empty?
        if (!(*cursor_it)->empty())
        {
            // Return.
            return true;
        }

        // Advance.
        ++cursor_it;
    }

    // Return.
    return false;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if a servicer is available
 *
 * @return Boolean value indicating if a servicer is available
 *
 */
bool ServiceQueueSimulation::is_servicer_available(std::shared_ptr< Servicer >) const
{
    // Get servicer iterators.
    auto cursor_it = servicers_.begin();
    auto end_it = servicers_.end();

    // Check each.
    while (cursor_it != end_it)
    {
        // Available?
        if (cursor_it->available(current_sim_time_))
        {
            // Return.
            return true;
        }

        // Advance.
        ++cursor_it;
    }

    // Return.
    return false;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a shared pointer to the next customer that should be
 *          serviced and removes them from their queue
 *
 * @return Pointer to the next customer that should be serviced
 *
 */
std::shared_ptr< Customer > ServiceQueueSimulation::next_customer_to_be_serviced() const
{
    // Get queue iterators.
    auto q_cursor_it = customer_queues_.begin();
    auto q_end_it = customer_queues_.end();

    // List of customer pointers.
    auto customer_ptrs = std::list< std::shared_ptr< Customer > >();

    // Get customers at the front of their queues.

    // Get customer
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