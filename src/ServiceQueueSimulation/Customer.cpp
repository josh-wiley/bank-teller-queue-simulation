/**
 *
 * @file Customer.cpp
 *
 * @brief Class for simulating a customer
 *
 * @author Josh Wiley
 *
 * @details Implements the Customer class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef CUSTOMER_CPP_
#define CUSTOMER_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "Customer.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Default constructor
 *
 */
Customer::Customer()
    : is_waiting_for_service_(false), arrival_time_(0),
      transaction_length_(0), departure_time_(0) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Stores paramaters as initial state and default inititializes other
 *          private members
 *
 * @param[in] arrival_time
 *            The time at which the customer is available for service
 *
 * @param[in] transaction_length
 *            The time which the customer's transaction will take
 *
 */
Customer::Customer(unsigned int arrival_time, unsigned int transaction_length)
    : is_waiting_for_service_(false), arrival_time_(arrival_time),
      transaction_length_(transaction_length), departure_time_(0) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy initializes customer object
 *
 * @param[in] origin
 *            Origin object from which the new object is to be instantiated with
 *
 */
Customer::Customer(const Customer& origin)
    : is_waiting_for_service_(origin.is_waiting_for_service_),
      arrival_time_(origin.arrival_time_),
      transaction_length_(origin.transaction_length_),
      departure_time_(origin.departure_time_) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
Customer::~Customer() {}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // CUSTOMER_CPP_
//