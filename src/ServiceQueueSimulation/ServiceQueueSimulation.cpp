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
    : current_sim_time_(0)
{
    // Events source iterators.
    auto events_cursor_it = events_ptr->begin();
    auto events_end_it = events_ptr->end();

    // Construct events list from source.
    while (events_cursor_it != events_end_it)
    {
        // Copy customer event.
        customer_events_.push_back(
            std::shared_ptr< Customer >(
                new Customer(
                    events_cursor_it->arrival_time(),
                    events_cursor_it->transaction_length()
                )
            )
        );

        // Advance.
        ++events_cursor_it;
    }

    // Create servicers.
    for (auto i = (unsigned int) 0; i < num_servicers; i++)
    {
        // Push new servicer to list.
        servicers_.push_back(
            std::shared_ptr< Servicer >( new Servicer() )
        );
    }
    
    // Add queues.
    add_queue(queue_ptr, rest_ptrs...);

    // Add line length lists.
    for (auto i = (unsigned int) 0; i < customer_queues_.size(); i++)
    {
        // Add list.
        line_lengths_.push_back(std::list< unsigned int >());
    }
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
    : current_sim_time_(origin.current_sim_time_), servicers_(origin.servicers_),
      customer_queues_(origin.customer_queues_), customer_events_(origin.customer_events_),
      start_time_(origin.start_time_), end_time_(origin.end_time_),
      line_lengths_(origin.line_lengths_) {}
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
 * @details Returns number of milliseconds the simulation took to complete
 *
 * @return Number of milliseconds that the simulation took to complete
 *
 */
unsigned int ServiceQueueSimulation::time_elapsed() const
{
    // Return milliseconds elapsed.
    return std::chrono::duration_cast
        < std::chrono::milliseconds >
            (end_time_ - start_time_)
                .count();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns current amount of simulation (virtual) time has passed in
 *          current simulation
 *
 * @return Elapsed simulation time
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
    // Get event iterators.
    auto ce_cursor_it = customer_events_.begin();
    auto ce_end_it = customer_events_.end();

    // Total wait time.
    auto total_wait = 0;
    auto total_events = 0;

    // Each events list.
    while(ce_cursor_it != ce_end_it)
    {
        // Wait time.
        total_wait += (*ce_cursor_it)->departure_time() - (*ce_cursor_it)->transaction_length() - (*ce_cursor_it)->arrival_time();

        // Total.
        total_events++;

        // Advance.
        ++ce_cursor_it;
    }

    // Return.
    return total_wait / total_events;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Computes and returns max customer wait time
 *
 * @return Max wait time for all customers
 *
 */
unsigned int ServiceQueueSimulation::max_customer_wait_time() const
{
    // Get event iterators.
    auto ce_cursor_it = customer_events_.begin();
    auto ce_end_it = customer_events_.end();

    // Total wait time.
    auto current_wait = 0;
    auto max_wait = 0;

    // Each events list.
    while(ce_cursor_it != ce_end_it)
    {
        // Get wait time.
        current_wait = (*ce_cursor_it)->departure_time() - (*ce_cursor_it)->transaction_length() - (*ce_cursor_it)->arrival_time();

        // Is new max?
        if (current_wait > max_wait)
        {
            // Assign new max.
            max_wait = current_wait;
        }

        // Advance.
        ++ce_cursor_it;
    }

    // Return max.
    return max_wait;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Computes and returns average line length of simulation
 *
 * @return Average line length of simulation
 *
 */
float ServiceQueueSimulation::average_line_length() const
{
    // Line length iterators.
    auto ll_cursor_it = line_lengths_.begin();
    auto ll_end_it = line_lengths_.end();

    // Sum.
    auto sum = (unsigned int) 0;

    // Average line lengths.
    auto line_length_averages = std::list< float >();

    while (ll_cursor_it != ll_end_it)
    {
        // Iterators.
        auto cursor_it = ll_cursor_it->begin();
        auto end_it = ll_cursor_it->end();

        // Find sum.
        while (cursor_it != end_it)
        {
            // Add.
            sum += *cursor_it;

            // Advance.
            ++cursor_it;
        }

        // Add average to list.
        line_length_averages.push_back(sum / ll_cursor_it->size());

        // Clear sum.
        sum = 0;

        // Advance.
        ++ll_cursor_it;
    }

    // Line averages iterators.
    auto la_cursor_it = line_length_averages.begin();
    auto la_end_it = line_length_averages.end();

    // Find sum of the averages.
    while (la_cursor_it != la_end_it)
    {
        // Add to sum.
        sum += *la_cursor_it;
        
        // Advance.
        ++la_cursor_it;
    }

    // Return average of averages.
    return sum / line_length_averages.size();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns max line length of simulation
 *
 * @return Max line length of simulation
 *
 */
unsigned int ServiceQueueSimulation::max_line_length() const
{
    // Line update iterators.
    auto ll_cursor_it = line_lengths_.begin();
    auto ll_end_it = line_lengths_.end();

    // Max line length.
    auto max_line_length = (unsigned int) 0;

    // Find max line length of all of the queues.
    while (ll_cursor_it != ll_end_it)
    {
        // Iterators.
        auto cursor_it = ll_cursor_it->begin();
        auto end_it = ll_cursor_it->end();

        // Find max.
        while (cursor_it != end_it)
        {
            // Is max?
            if (*cursor_it > max_line_length)
            {
                // Assign new max.
                max_line_length = *cursor_it;
            }

            // Advance.
            ++cursor_it;
        }

        // Advance.
        ++ll_cursor_it;
    }

    // Return.
    return max_line_length;
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
    // Pointer to list of idle times.
    auto totals_list_ptr = std::shared_ptr< std::list< unsigned int > >(
        new std::list< unsigned int >()
    );

    // Add totals.
    std::for_each(servicers_.begin(), servicers_.end(), [totals_list_ptr] (auto servicer_ptr)
    {
        // Add idle time.
        totals_list_ptr->push_back(servicer_ptr->total_idle_time());
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
    // Start time.
    start_time_ = std::chrono::high_resolution_clock::now();

    // Event iterators.
    auto next_arrival_it = customer_events_.begin();
    auto end_it = customer_events_.end();
    
    // Cached results.
    auto next_arrival_time = (*next_arrival_it)->arrival_time();
    auto next_departure_time = (unsigned int) 0;

    // Pointer to servicer and customer to process a transaction.
    auto servicer_ptr = std::shared_ptr< Servicer >();
    auto customer_ptr = std::shared_ptr< Customer>();

    // Pending events?
    while (
        // Arrival events to be processed?
        next_arrival_it != end_it ||

        // Departure events to be processed? 
        next_departure_time != 0 ||

        // Working servicers?
        !all_servicers_idle()
    )
    {
        // Arrival?
        if (
            // If there is an arrival event to process.
            next_arrival_it != end_it &&
            (
                // If there is no departure event.
                next_departure_time == 0 ||
                
                // Or if the next departure event is after the next arrival event.
                next_departure_time > next_arrival_time
            )
        )
        {
            // Advance time to next arrival.
            current_sim_time_ = next_arrival_time;

            // Enqueue.
            enqueue_to_shortest_queue(*next_arrival_it);

            // Advance iterator.
            ++next_arrival_it;

            // Is the next arrival iterator is valid?
            if (next_arrival_it != end_it)
            {
                // Cache new arrival time.
                next_arrival_time = (*next_arrival_it)->arrival_time();
            }
        }
        // Departure?
        else if (next_departure_time != 0)
        {
            // Fast-forward to next departure time.
            current_sim_time_ = next_departure_time;
        }

        // Are waiting customers and servicers available?
        while (is_servicer_available(servicer_ptr) && is_customer_waiting(customer_ptr))
        {
            // Service customer.
            servicer_ptr->service_customer(current_sim_time_, customer_ptr);
        }

        // Update next departure time.
        next_departure_time = get_next_departure_time();
    }

    // End time.
    end_time_ = std::chrono::high_resolution_clock::now();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Enqueues customer pointer to shortest queue
 *
 * @param[in] customer_ptr
 *            Smart pointer to the customer that should be enqueued.
 *
 */
void ServiceQueueSimulation::enqueue_to_shortest_queue(std::shared_ptr< Customer > customer_ptr)
{
    // Pointer to shortest queue, cursor, and end.
    auto shortest_queue_ptr_it = customer_queues_.begin();
    auto cq_cursor_it = next(shortest_queue_ptr_it);
    auto cq_end_it = customer_queues_.end();

    // Line length iterators.
    auto shortest_line_length_it = line_lengths_.begin();
    auto ll_cursor_it = next(shortest_line_length_it);

    // Find smallest queue.
    while(cq_cursor_it != cq_end_it)
    {
        // Shorter than current shortest?
        if ((*shortest_queue_ptr_it)->size() > (*cq_cursor_it)->size())
        {
            // Update new shortest queue.
            shortest_queue_ptr_it = cq_cursor_it;

            // Update iterator to appropriate line length list.
            shortest_line_length_it = ll_cursor_it;
        }

        // Advance.
        ++cq_cursor_it;
        ++ll_cursor_it;
    }

    // Enqueue.
    (*shortest_queue_ptr_it)->enqueue(customer_ptr);

    // Update line length.
    shortest_line_length_it->push_back((*shortest_queue_ptr_it)->size());
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
        // Is servicer not available?
        if (!(*cursor_it)->available(current_sim_time_))
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
unsigned int ServiceQueueSimulation::get_next_departure_time() const
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
        if (!(*s_cursor_it)->available(current_sim_time_))
        {
            // Get departure time.
            departure_times.push_back((*s_cursor_it)->unavailable_until());
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
 * @param[out] next_customer_ptr
 *             Pointer to be assigned the customer who has been waiting the longest.
 *
 * @return Boolean value indicating if there are any customers waiting for
 *         service
 *
 */
bool ServiceQueueSimulation::is_customer_waiting(std::shared_ptr< Customer >& next_customer_ptr)
{
    // Get queue iterators.
    auto cq_cursor_it = customer_queues_.begin();
    auto cq_end_it = customer_queues_.end();

    // List of queue pointers.
    auto loaded_queues = std::list< std::shared_ptr< Queue < std::shared_ptr< Customer > > > >();

    // Line length iterators.
    auto ll_cursor_it = line_lengths_.begin();

    // List of iterators pointing to line lengths associated with the loaded queues.
    auto line_lenghts_its = std::list< std::list< std::list< unsigned int > >::iterator >();

    // Check each.
    while (cq_cursor_it != cq_end_it)
    {
        // Not empty?
        if (!(*cq_cursor_it)->empty())
        {
            // Add to lists.
            loaded_queues.push_back(*cq_cursor_it);
            line_lenghts_its.push_back(ll_cursor_it);
        }

        // Advance.
        ++cq_cursor_it;
        ++ll_cursor_it;
    }

    // If no queues with customers, return.
    if (loaded_queues.empty())
    {
        // Return.
        return false;
    }

    // Get loaded queue iterators.
    auto lq_cursor_it = loaded_queues.begin();
    auto lq_end_it = loaded_queues.end();

    // Loaded line length iterators.
    auto lll_cursor_it = line_lenghts_its.begin();

    // Queue to dequeue from.
    auto queue_to_dequeue_from_ptr = std::shared_ptr< Queue < std::shared_ptr< Customer > > >
        (*lq_cursor_it);
    auto lll_to_dequeue_from = *lll_cursor_it;

    // Get first customer arrival time.
    auto earliest_arrival_time =
        queue_to_dequeue_from_ptr
            ->peek()
            ->arrival_time();

    // Advance.
    ++lq_cursor_it;
    ++lll_cursor_it;

    // Get queue to dequeue from.
    while (lq_cursor_it != lq_end_it)
    {
        // Is earlier arrival time.
        if ((*lq_cursor_it)->peek()->arrival_time() < earliest_arrival_time)
        {
            // Save queue pointer.
            queue_to_dequeue_from_ptr =
                std::shared_ptr
                    < Queue < std::shared_ptr< Customer > > >
                    (*lq_cursor_it);

            // Save new arrival time.
            earliest_arrival_time =
                queue_to_dequeue_from_ptr
                    ->peek()
                    ->arrival_time();
            
            // Save iterator to list to keep track of line updates.
            lll_to_dequeue_from = *lll_cursor_it;
        }

        // Advance.
        ++lq_cursor_it;
        ++lll_cursor_it;
    }

    // Save.
    next_customer_ptr = queue_to_dequeue_from_ptr->peek();

    // Dequeue.
    queue_to_dequeue_from_ptr->dequeue();

    // Update line length.
    lll_to_dequeue_from->push_back(queue_to_dequeue_from_ptr->size());

    // Return.
    return true;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if a servicer is available
 *
 * @param[out] available_servicer
 *             Pointer to assign an available servicer to
 *
 * @return Boolean value indicating if a servicer is available
 *
 */
bool ServiceQueueSimulation::is_servicer_available(std::shared_ptr< Servicer >& available_servicer) const
{
    // Get servicer iterators.
    auto cursor_it = servicers_.begin();
    auto end_it = servicers_.end();

    // Check each.
    while (cursor_it != end_it)
    {
        // Available?
        if ((*cursor_it)->available(current_sim_time_))
        {
            // Save out parameter.
            available_servicer = *cursor_it;

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