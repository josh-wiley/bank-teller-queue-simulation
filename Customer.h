/**
 *
 * @file Customer.h
 *
 * @brief Class for simulating a customer
 *
 * @author Josh Wiley
 *
 * @details Defines the Customer class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef CUSTOMER_H_
#define CUSTOMER_H_
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class Customer
{

// Public members.
public:
    Customer(); /**< Default constructor */
    Customer(const Customer&); /**< Copy constructor */
    ~Customer(); /**< Destructor */

// Private members.
private:
    unsigned int arrival_time_;  /**< Time of arrival */
    unsigned int transaction_time_;  /**< Length of transaction */
    unsigned int departure_time_;  /**< Time of departure */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // CUSTOMER_H_
//