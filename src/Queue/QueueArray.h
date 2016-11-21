/**
 *
 * @file QueueArray.h
 *
 * @brief Templated queue with dynamically-allocated array container
 *
 * @author Josh Wiley
 *
 * @details Defines the QueueArray class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef QUEUE_ARRAY_H_
#define QUEUE_ARRAY_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <list>
#include <iterator>
#include <utility>
#include <memory>
#include "Queue.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
template<class T>
class QueueArray : public Queue< T >
{

// Public members.
public:
  QueueArray(size_t, std::shared_ptr< std::list< T > > data_ptr = std::shared_ptr< std::list< T > >(nullptr)); /**< Parameterized constructor */
  QueueArray(const QueueArray< T >&); /**< Copy constructor */
  ~QueueArray(); /**< Destructor */

  bool empty() const override; /**< Returns boolean indicating if queue is empty */
  bool enqueue(T) override; /**< Places an item at the end of the queue and returns boolean indicating success */
  bool dequeue() override; /**< Removes and returns the item in the front of the queue */
  T peek() const override; /**< Returns the item in the front of the queue without modifying the data */
  size_t size() const override; /** Returns size of queue */

  QueueArray<T> operator=(const QueueArray< T >&); /**< Overloaded assignment operator. */

// Private members.
private:
  size_t max() const; /**< Returns max size of queue */
  
  std::shared_ptr< T > data_set_ptr_; /**< Underlying data container */
  size_t begin_; /**< Current front index */
  size_t end_; /**< Current index indicating first out-of-bound index */
  size_t max_; /** Max size of queue */

};
//
//  Implementation Files  //////////////////////////////////////////////////////
//
#include "QueueArray.cpp"
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // QUEUE_ARRAY_H_
//
