/**
 *
 * @file Servicer.cpp
 *
 * @brief Class for simulating a servicer
 *
 * @author Josh Wiley
 *
 * @details Implements the Servicer class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef SERVICER_CPP_
#define SERVICER_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "Servicer.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Default constructor
 *
 */
Servicer::Servicer()
    : unavailable_until_(0), total_idle_time_(0) {}
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
Servicer::Servicer(const Servicer& origin)
    : unavailable_until_(origin.unavailable_until_), total_idle_time_(origin.total_idle_time_) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
Servicer::~Servicer() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Services customer and updates availability
 *
 * @param[in] current_time
 *            Time at which the servicing is requested
 *
 * @param[out] customer_ptr
 *             Allows servicer to update state of customer
 *
 * @return Boolean value indicating whether the servicer is currently
 *         unavailable
 *
 */
bool Servicer::service_customer(unsigned int current_time, Customer* customer_ptr)
{
    // Is unavailale?
    if (!available(current_time))
    {
        // Failure.
        return false;
    }

    // Complete transaction.
    customer_ptr->complete_transaction(current_time);

    // Update idle time.
    total_idle_time_ += current_time - unavailable_until_;

    // Update availability.
    unavailable_until_ = current_time + customer_ptr->transaction_length();
    
    // Successful.
    return true;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns boolean indicating whether or not the servicer is currently
 *          available
 *
 * @return Boolean value indicating whether or not the servicer is currently
 *         available
 *
 */
bool Servicer::available(unsigned int current_time) const
{
    // Return availability state of servicer.
    return unavailable_until_ <= current_time;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns number indicating total time servicer has been idle
 *
 * @return Unsigned integer value representing the servicer's total idle time
 *
 */
unsigned int Servicer::total_idle_time() const
{
    // Return total idle time.
    return total_idle_time_;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICER_CPP_
//