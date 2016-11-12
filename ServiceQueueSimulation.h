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
#include <utility>
#include "Queue.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class ServiceQueueSimulation
{
public:
    ServiceQueueSimulation(std::shared_ptr< std::list<Queue < std::pair< unsigned int, unsigned int > > > >, unsigned int servicers = 1);
    ServiceQueueSimulation(const ServiceQueueSimulation&);
    ~ServiceQueueSimulation();

private:

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICE_QUEUE_SIMULATION_H_
//