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
    Customer(unsigned int, unsigned int); /**< Parameterized constructor */
    Customer(const Customer&); /**< Copy constructor */
    ~Customer(); /**< Destructor */

    bool is_waiting_for_service() const; /**< Returns boolean value indicating if the customer is waiting for service */
    unsigned int arrival_time() const; /**< Return the time of arrival */
    unsigned int transaction_length() const; /**< Return the length of the transaction */
    unsigned int departure_time() const; /**< Return the time of departure */
    bool complete_transaction(unsigned int); /**< Set departure time */

// Private members.
private:
    bool is_waiting_for_service_; /**< Is the customer waiting for service? */
    unsigned int arrival_time_;  /**< Time of arrival */
    unsigned int transaction_length_;  /**< Length of transaction */
    unsigned int departure_time_;  /**< Time of departure */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // CUSTOMER_H_
//