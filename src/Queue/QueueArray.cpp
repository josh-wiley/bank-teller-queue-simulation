/**
 *
 * @file QueueArray.cpp
 *
 * @brief Templated queue with dynamically-allocated array container
 *
 * @author Josh Wiley
 *
 * @details Implements the QueueArray class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef QUEUE_ARRAY_CPP_
#define QUEUE_ARRAY_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "QueueArray.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Allocates heap memory and copies data if pointer provided is valid
 *
 * @param[in] max_size
 *            The maximum size (determines heap memory allocated)
 *
 * @param[in] data_ptr
 *            Pointer to the list to import
 *
 */
template<typename T>
QueueArray<T>::QueueArray(size_t max_size, std::shared_ptr< std::list<T> > data_ptr)
    : begin_(0), max_(max_size)
{
    // Allocate.
    data_set_ptr_.reset(new T[max_], [] (auto ptr) { delete[] ptr; });
    
    // Is pointer valid?
    if (data_ptr.get() != nullptr)
    {
        // Size.
        end_ = data_ptr->size();

        // Cursor.
        auto cursor = data_ptr->begin();

        // Copy data set.
        for (auto i = 0; cursor != data_ptr->end(); i++)
        {
            // Copy.
            data_set_ptr_.get()[i] = *cursor;

            // Advance.
            ++cursor;
        }
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes queue from another queue
 *
 */
template<typename T>
QueueArray<T>::QueueArray(const QueueArray<T>& origin)
    : begin_(origin.begin_ % origin.max_), end_((origin.end_ % origin.max_) + 1), max_(origin.max_)
{
    // Allocate.
    data_set_ptr_.reset(new T[max_], [] (auto ptr) { delete[] ptr; });

    // Is pointer valid?
    if (origin.data_set_ptr_ != nullptr)
    {
        // Size.
        end_ = origin.size();

        // Copy data set.
        for (auto i = origin.begin_; i < origin.end_; i++)
        {
            // Copy item.
            data_set_ptr_.get()[i % max_] = origin.data_set_ptr_.get()[i % max_];
        }
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
template<typename T>
QueueArray<T>::~QueueArray() {}
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
bool QueueArray<T>::empty() const
{
  // Return empty status.
  return begin_ == end_;
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
bool QueueArray<T>::enqueue(T input)
{
  // Available space?
  if (max_ - size() > 0)
  {
      // Failure.
      return false;
  }

  // Place value.
  data_set_ptr_.get()[end_ - 1] = input;

  // Increment end.
  end_++;

  // Success.
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
bool QueueArray<T>::dequeue()
{
  // Empty?
  if (empty())
  {
    // Return failure.
    return false;
  }

  // Increment front.
  begin_++;

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
T QueueArray<T>::peek() const
{
  // Return front item.
  return data_set_ptr_.get()[begin_];
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
size_t QueueArray<T>::size() const
{
    // Return size of queue.
    return end_ - 1 - begin_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns maximum size of queue.
 *
 * @return Maximum size of queue.
 *
 */
template<typename T>
size_t QueueArray<T>::max() const
{
    // Return max size.
    return max_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Overloaded assignment operator.
 *
 * @return Reference to this object for chain assignments.
 *
 */
template<typename T>
QueueArray<T> QueueArray<T>::operator=(const QueueArray<T>& rhs)
{
    // Reallocate.
    *data_set_ptr_.reset(new T[rhs.max_], [] (auto ptr) { delete[] ptr; });

    // Is pointer valid?
    if (rhs.data_set_ptr_ != nullptr)
    {
        // Copy.
        for (auto i = rhs.begin_; i < rhs.end_; i++)
        {
            // Copy item.
            data_set_ptr_.get()[i % max_] = rhs.data_set_ptr_.get()[i];
        }
    }

    // Return.
    return this;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // QUEUE_ARRAY_CPP_
//
