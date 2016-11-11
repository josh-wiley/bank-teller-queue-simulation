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
//
//  Class Definition  //////////////////////////////////////////////////////////
//
template<class T>
class QueueList
{

// Public members.
public:
  QueueList(); /**< Default constructor */
  QueueList(std::shared_ptr<std::list<T>>); /**< Parameterized constructor */
  QueueList(const QueueList<T>&); /**< Copy constructor */
  ~QueueList(); /**< Destructor */

  bool empty() const; /**< Returns boolean indicating if queue is empty */
  bool enqueue(T); /**< Places an item at the end of the queue and returns boolean indicating success */
  bool dequeue(); /**< Removes and returns the item in the front of the queue */
  T peek() const; /**< Returns the item in the front of the queue without modifying the data */

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
