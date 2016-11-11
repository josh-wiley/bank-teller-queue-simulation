/**
 *
 * @file data_generator.h
 *
 * @brief Namespace for test data generation utilities.
 *
 * @author Josh Wiley
 *
 * @details Provides efficient convenience functions for generating test data
 *          sets.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef DATA_GENERATOR_H_
#define DATA_GENERATOR_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <cstdlib>
#include <chrono>
#include <list>
#include <memory>
//
//  Namespace Definition  //////////////////////////////////////////////////////
//
namespace data_generator
{
  // Generate random integer data set.
  void generateRandomData(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, std::shared_ptr<std::list<std::pair<unsigned int, unsigned int>>>); /**< Generates random numbers and stores in list parameter. */
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // DATA_SET_GENERATOR_H_
//
