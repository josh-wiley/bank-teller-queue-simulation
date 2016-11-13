/**
 *
 * @file data_generator.cpp
 *
 * @brief Implements test generation utility functions.
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
#ifndef DATA_GENERATOR_CPP_
#define DATA_GENERATOR_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "data_generator.h"
//
//  Function Implementation  /////////////////////////////////////////////////
//
/**
 *
 * @brief Generates pairs of random numbers and places them into provided list
 *
 * @details Generates the specified amount of random, unsigned integers pairs
 *          which have a range determined by the arguments supplied
 *
 * @param[in] size
 *            The number of random values and final size of the data set
 *
 * @param[in] left_min
 *            Minimum value for items on the left side of each pair
 *
 * @param[in] left_max
 *            Maximum value for items on the left side of each pair
 *
 * @param[in] right_min
 *            Minimum value for items on the right side of each pair
 *
 * @param[in] right_max
 *            Maximum value for items on the right side of each pair
 *
 * @param[out] data_set_ptr
 *             A shared pointer to the container that data will be placed into
 *
 */
void data_generator::generateRandomData(unsigned int size, unsigned int left_min, unsigned int left_max, unsigned int right_min, unsigned int right_max, std::shared_ptr<std::list<std::pair<unsigned int, unsigned int>>> data_set_ptr)
{
  // Ensure data set is empty.
  data_set_ptr->clear();

  // Seed the random value generator.
  std::srand(
    std::chrono::high_resolution_clock::now()
    .time_since_epoch()
    .count()
  );

  // Generate data set.
  for (unsigned int i = 0; i < size; i++)
  {
    // Emplace pair of random values.
    data_set_ptr->emplace_back(
      std::make_pair(
        ((unsigned int) std::rand() % (left_max + 1 - left_min)) + left_min,
        ((unsigned int) std::rand() % (right_max + 1 - right_min)) + right_min
      )
    );
  }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // DATA_GENERATOR_CPP_
//
