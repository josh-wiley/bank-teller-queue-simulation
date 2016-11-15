/**
 *
 * @file sorter.h
 *
 * @brief Namespace for counting sort algorithm.
 *
 * @author Josh Wiley
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef SORTER_CPP_
#define SORTER_CPP_
//
//  Header File  ///////////////////////////////////////////////////////////////
//
#include "sorter.h"
//
//  Function Implementation  ///////////////////////////////////////////////////
//
/**
 *
 * @brief Sorts the provided data set using quick sort
 *
 * @details Sorts the provided data set with the quick sort algorithm
 *
 * @param[in] begin_it
 *            An iterator pointing to the first item in the data set
 *
 * @param[in] end_it
 *            The terminating iterator used to determine the end of the data set
 *
 */
void sorter::counting_sort_by_arrival_time(std::list< Customer >::iterator begin_it, std::list< Customer >::iterator end_it, unsigned int min_value, unsigned int max_value)
{
  // Array of frequencies.
  auto frequencies = std::shared_ptr<unsigned int>(
    new unsigned int[(max_value - min_value) + 1],
    [] (auto ptr) { delete[] ptr; }
  );

  // Array buffer of sorted values (for random-access in insertion).
  auto temp_result = std::shared_ptr< Customer >(
    new Customer[distance(begin_it, end_it)],
    [] (auto ptr) { delete[] ptr; }
  );

  // Copy of data set.
  auto data_copy = std::list< Customer >();

  // Clear frequencies.
  for (unsigned int i = 0; i < max_value + 1; i++)
  {
    // Set inital value.
    frequencies.get()[i] = 0;
  }

  // Acquire value frequencies.
  std::for_each(begin_it, end_it, [&, frequencies] (auto i)
  {
    // Increment.
    frequencies.get()[i.arrival_time()]++;

    // Add to copy.
    data_copy.push_back(i);
  });

  // Calculate max indexes based on frequencies.
  for (unsigned int i = 1; i < max_value + 1; i++)
  {
    // Add previous value to current value.
    frequencies.get()[i] += frequencies.get()[i - 1];
  }

  // Overwrite in correct order.
  std::for_each(data_copy.rbegin(), data_copy.rend(), [&, frequencies, temp_result] (auto i)
  {
    // Decrement and insert at index.
    temp_result.get()[--frequencies.get()[i.arrival_time()]] = i;
  });

  // Cursor.
  auto cursor_it = begin_it;

  // Overwrite with results.
  for (auto i = 0; cursor_it != end_it; i++)
  {
    // Copy.
    *cursor_it = temp_result.get()[i];

    // Advance.
    ++cursor_it;
  }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SORTER_CPP_
//
