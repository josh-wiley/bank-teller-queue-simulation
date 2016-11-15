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
 * @details Constructs customer queues and list of servicers
 *
 * @param[in] queues_ptr
 *            A smart pointer to the list of queues representing customers
 *
 * @param[in] servicers
 *            The number of servicers available to serve the queues of customers
 *
 */
ServiceQueueSimulation::ServiceQueueSimulation(std::shared_ptr< std::list< Queue < Customer >* > > queues_ptr, unsigned int num_servicers)
{
    // Copy customer queues.
    customer_queues_ = *queues_ptr;

    // Ensure servicers list is in initial state.
    servicers_.clear();

    // Create servicers.
    for (auto i = 0; i < num_servicers; i++)
    {
        // Push new servicer to list.
        servicers_.push_back(Servicer());
    }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICE_QUEUE_SIMULATION_CPP_
//