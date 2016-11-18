/**
 *
 * @file Logger.h
 *
 * @brief Logger class for logging assignment state and data to a file
 *
 * @author Josh Wiley
 *
 * @details Defines the Logger class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef LOGGER_H_
#define LOGGER_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <fstream>
#include <string>
#include <memory>
#include <list>
#include <utility>
#include <iterator>
#include "../ServiceQueueSimulation/Customer.h"
#include "../ServiceQueueSimulation/ServiceQueueSimulation.h"
//
//  Class Definition  //////////////////////////////////////////////////////////
//
class Logger
{

// Public members.
public:
    Logger(std::string file_name); /**< Parameterized constructor */
    Logger(const Logger&); /**< Copy constructor */
    ~Logger(); /**< Destructor */

    void log_customer_list(
        std::string,
        std::shared_ptr< std::list< Customer > >
    ); /**< Logs list of pairs to file */
    void log_sim_results(
        std::string,
        std::shared_ptr< ServiceQueueSimulation >
    ); /**< Logs simulation results to file */

// Private members.
private:
    std::string file_name_; /**< Output file name */
    std::ofstream file_stream_; /**< Output file stream */

};
//
//  Implementation Files  //////////////////////////////////////////////////////
//
#include "Logger.cpp"
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // LOGGER_H_
//