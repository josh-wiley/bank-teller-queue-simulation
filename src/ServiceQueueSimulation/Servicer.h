/**
 *
 * @file Servicer.h
 *
 * @brief Class for simulating a servicer
 *
 * @author Josh Wiley
 *
 * @details Defines the Servicer class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef SERVICER_H_
#define SERVICER_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "Customer.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class Servicer
{

// Public members.
public:
    Servicer(); /**< Default constructor */
    Servicer(const Servicer&); /**< Copy constructor */
    ~Servicer(); /**< Destructor */

    bool handle_customer(unsigned int, Customer&); /**< Handles customer at current time */
    bool available(unsigned int) const;  /**< Returns availability state of servicer at given time */
    unsigned int total_idle_time() const; /**< Returns current total idle time for servicer */

// Private members.
private:
    bool unavailable_until_;  /**< Servicer availability state */
    unsigned int total_idle_time_; /**< Total time that servicer has been idle */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICER_H_
//