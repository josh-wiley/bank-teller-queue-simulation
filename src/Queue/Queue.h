/**
 *
 * @file Queue.h
 *
 * @brief Abstract base class for queues
 *
 * @author Josh Wiley
 *
 * @details Defines the Queue abstract base class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef QUEUE_H_
#define QUEUE_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <cstddef>
//
//  Class Definition  //////////////////////////////////////////////////////////
//
template<class T>
class Queue
{

// Public members.
public:
    virtual bool empty() const = 0; /**< Returns boolean indicating if queue is empty */
    virtual bool enqueue(T) = 0; /**< Places an item at the end of the queue and returns boolean indicating success */
    virtual bool dequeue() = 0; /**< Removes and returns the item in the front of the queue */
    virtual T peek() const = 0; /**< Returns the item in the front of the queue without modifying the data */
    virtual size_t size() const = 0; /**< Returns size of queue */
};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // QUEUE_H_
//