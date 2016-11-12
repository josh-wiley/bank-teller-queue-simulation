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
//
//  Class Definition  //////////////////////////////////////////////////////////
//
template<class T>
class QueueArray
{

// Public members.
public:
  QueueArray(size_t, std::shared_ptr< std::list<T> >); /**< Parameterized constructor */
  QueueArray(const QueueArray<T>&); /**< Copy constructor */
  ~QueueArray(); /**< Destructor */

  bool empty() const; /**< Returns boolean indicating if queue is empty */
  bool enqueue(T); /**< Places an item at the end of the queue and returns boolean indicating success */
  bool dequeue(); /**< Removes and returns the item in the front of the queue */
  T peek() const; /**< Returns the item in the front of the queue without modifying the data */

  QueueArray<T> operator=(const QueueArray<T>&); /**< Overloaded assignment operator. */

// Private members.
private:
  size_t size() const; /**< Returns current size of queue */
  size_t max() const; /**< Returns max size of queue */
  
  std::shared_ptr<T> data_set_ptr_; /**< Underlying data container */
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
