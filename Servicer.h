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

    bool handle_customer(unsigned int, Customer&);
    bool available() const;  /**< Returns availability state of servicer */

// Private members.
private:
    bool is_available_;  /**< Servicer availability state */

};
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // SERVICER_H_
//