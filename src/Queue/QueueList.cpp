/**
 *
 * @file QueueList.cpp
 *
 * @brief Templated queue with doubly-linked list container
 *
 * @author Josh Wiley
 *
 * @details Implements the QueueList class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef QUEUE_LIST_CPP_
#define QUEUE_LIST_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "QueueList.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Default initializes data set
 *
 */
template<typename T>
QueueList<T>::QueueList() : data_set_(std::list<T>()) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copies list as underlying data set
 *
 */
template<typename T>
QueueList<T>::QueueList(std::shared_ptr<std::list<T>> data_set_ptr) : data_set_(*data_set_ptr) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes queue from another queue
 *
 */
template<typename T>
QueueList<T>::QueueList(const QueueList<T>& origin) : data_set_(origin.data_set_) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
template<typename T>
QueueList<T>::~QueueList() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean indicating whether or not the queue is empty
 *
 * @return Boolean value indicating whether or not the queue is empty
 *
 */
template<typename T>
bool QueueList<T>::empty() const
{
  // Return empty status.
  return data_set_.empty();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Attempts to place an item at the end of the queue and returns a
 *          boolean value indicating the success of the operation
 *
 * @param[in] input
 *            Item to place at the end of the queue
 *
 * @return Boolean value indicating the success of the operation
 *
 */
template<typename T>
bool QueueList<T>::enqueue(T input)
{
  // Push item to end of queue.
  data_set_.push_back(input);

  // Always successful for this implementation.
  return true;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Removes the item at the front of the queue
 *
 * @return Boolean value indicating the success of the operation.
 *
 */
template<typename T>
bool QueueList<T>::dequeue()
{
  // Empty?
  if (empty())
  {
    // Return failure.
    return false;
  }

  // Remove item.
  data_set_.pop_front();

  // Return success.
  return true;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Removes the item at the front of the queue
 *
 * @return Boolean value indicating the success of the operation.
 *
 */
template<typename T>
T QueueList<T>::peek() const
{
  // Return front item.
  return data_set_.front();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns current size of queue.
 *
 * @return Current size of queue.
 *
 */
template<typename T>
size_t QueueList<T>::size() const
{
    // Return size of queue.
    return data_set_.size();
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // QUEUE_LIST_CPP_
//
