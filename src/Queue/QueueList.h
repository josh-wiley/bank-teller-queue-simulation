/**
 *
 * @file QueueList.h
 *
 * @brief Templated queue with doubly-linked list container
 *
 * @author Josh Wiley
 *
 * @details Defines the QueueList class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef QUEUE_LIST_H_
#define QUEUE_LIST_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <list>
#include <memory>
#include "Queue.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
template<class T>
class QueueList : public Queue<T>
{

// Public members.
public:
  QueueList(); /**< Default constructor */
  QueueList(std::shared_ptr<std::list<T>>); /**< Parameterized constructor */
  QueueList(const QueueList<T>&); /**< Copy constructor */
  ~QueueList(); /**< Destructor */

  bool empty() const override; /**< Returns boolean indicating if queue is empty */
  bool enqueue(T) override; /**< Places an item at the end of the queue and returns boolean indicating success */
  bool dequeue() override; /**< Removes and returns the item in the front of the queue */
  T peek() const override; /**< Returns the item in the front of the queue without modifying the data */
  size_t size() const override; /** Returns size of queue */

// Private members.
private:
  std::list<T> data_set_; /**< Underlying data container */

};
//
//  Implementation Files  //////////////////////////////////////////////////////
//
#include "QueueList.cpp"
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // QUEUE_LIST_H_
//
