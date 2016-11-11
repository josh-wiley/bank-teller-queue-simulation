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
#include <iostream> // TODO: REMOVE
//
//  Namespace Definition  //////////////////////////////////////////////////////
//
namespace sorter
{
  // Counting sort.
  void counting_sort(std::list<std::pair<unsigned int, unsigned int>>::iterator, std::list<std::pair<unsigned int, unsigned int>>::iterator, unsigned int, unsigned int);
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SORTER_H_
//
