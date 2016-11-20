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
#include <memory>
#include "Customer.h"
#include <iostream> // TODO: REMOVE
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

    void service_customer(unsigned int, std::shared_ptr< Customer >); /**< Services customer at current time and updates availability */
    bool available(unsigned int) const;  /**< Returns availability state of servicer at given time */
    unsigned int total_idle_time() const; /**< Returns current total idle time for servicer */
    unsigned int unavailable_until() const; /**< Returns the time when the servicer will become available */

// Private members.
private:
    unsigned int unavailable_until_;  /**< Servicer availability state */
    unsigned int total_idle_time_; /**< Total time that servicer has been idle */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICER_H_
//