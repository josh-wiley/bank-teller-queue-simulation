/**
 *
 * @file sorter.h
 *
 * @brief Namespace for counting sort algorithms.
 *
 * @author Josh Wiley
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef SORTER_H_
#define SORTER_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <list>
#include <iterator>
#include <algorithm>
#include <memory>
#include <utility>
#include "../ServiceQueueSimulation/Customer.h"
//
//  Namespace Definition  //////////////////////////////////////////////////////
//
namespace sorter
{
  // Counting sort.
  void counting_sort_by_arrival_time(
    std::list< Customer >::iterator,
    std::list< Customer >::iterator,
    unsigned int,
    unsigned int
  );
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SORTER_H_
//
