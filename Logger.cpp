/**
 *
 * @file Logger.cpp
 *
 * @brief Logger class for logging assignment state and data to a file
 *
 * @author Josh Wiley
 *
 * @details Implements the Logger class
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef LOGGER_CPP_
#define LOGGER_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "Logger.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Parameterized constructor
 *
 * @param[in] name
 *            Name of output file
 *
 */
Logger::Logger(std::string name) : file_name_(name), file_stream_(std::ofstream(name)) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes queue
 *
 */
Logger::Logger(const Logger& origin)
    : file_name_(origin.file_name_), file_stream_(std::ofstream(origin.file_name_)) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
Logger::~Logger()
{
    // Close file stream.
    file_stream_.close();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Logs data set to file with specified header
 *
 * @param[in] header
 *            Header to be displayed in record
 *
 * @param[in] data_set_ptr
 *            Smart pointer to data set
 *
 */
void Logger::log_pair_list(std::string header, std::shared_ptr< std::list<std::pair< unsigned int, unsigned int> > > data_set_ptr)
{
    // Header.
    file_stream_ << "\n\n"
                 << "================================================================================\n"
                 << header << '\n'
                 << "================================================================================\n";
    
    // Cursor.
    auto cursor_it = data_set_ptr->begin();

    // End.
    auto end_it = data_set_ptr->end();
    
    // Output data set.
    for (auto i = 0; cursor_it != end_it; i++)
    {
        // Log.
        file_stream_ << i + 1 << ". Start time: " << std::get<0>(*cursor_it)
                              << ", End time: " << std::get<1>(*cursor_it) << '\n';

        // Advance.
        ++cursor_it;
    }

    // End.
    file_stream_ << "================================================================================\n";
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // LOGGER_CPP_
//