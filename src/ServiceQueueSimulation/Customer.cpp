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
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns waiting state of customer
 *
 * @return Boolean value indicating whether the customer is currently waiting
 *         for service
 *
 */
bool Customer::is_waiting_for_service() const
{
    // Return wating state.
    return is_waiting_for_service_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns number indicating arrival time
 *
 * @return Unsigned integer value representing the customer's arrival time
 *
 */
unsigned int Customer::arrival_time() const
{
    // Return arrival time.
    return arrival_time_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns number indicating length of customer transaction
 *
 * @return Unsigned integer value representing the customer's transaction length
 *
 */
unsigned int Customer::transaction_length() const
{
    // Return transaction length.
    return transaction_length_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns number indicating customer's departure time
 *
 * @return Unsigned integer value representing the customer's departure time 
 *         (if not departed, value is 0)
 *
 */
unsigned int Customer::departure_time() const
{
    // Return transaction length.
    return departure_time_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Sets customer departure time and returns boolean value indicating
 *          success of operation
 *
 * @param[in] transaction_time
 *            The time at which the transaction started
 *
 * @return Boolean value indicating whether or not the customer has already
 *         completed a transaction
 *
 */
bool Customer::complete_transaction(unsigned int transaction_time)
{
    // Transaction already completed?
    if (departure_time_ >= 0)
    {
        // Failure.
        return false;
    }

    // Set departure time.
    departure_time_ = transaction_time + transaction_length_;

    // Success.
    return true;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // CUSTOMER_CPP_
//