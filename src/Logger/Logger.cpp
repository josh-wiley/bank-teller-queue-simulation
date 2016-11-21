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
void Logger::log_customer_list(std::string header, std::shared_ptr< std::list< Customer > > data_set_ptr)
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
        file_stream_ << i + 1 << ". Arrival time: " << cursor_it->arrival_time()
                              << ", Transaction time: " << cursor_it->transaction_length() << '\n';

        // Advance.
        ++cursor_it;
    }

    // End.
    file_stream_ << "================================================================================\n";
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Logs simulation results to file with specified header
 *
 * @param[in] header
 *            Header to be displayed in record
 *
 * @param[in] sim_ptr
 *            Smart pointer to simulation
 *
 */
void Logger::log_sim_results(std::string header, std::shared_ptr< ServiceQueueSimulation > sim_ptr)
{
    // Output.
    file_stream_ << "\n\n"

                 // Header.
                 << "================================================================================\n"
                 << header << '\n'
                 << "================================================================================\n"
    
                 // CPU time.
                 << "CPU Time: " << sim_ptr->time_elapsed() << " milliseconds\n"

                 // Simulation time.
                 << "Simulation Time: " << sim_ptr->sim_time() << " simulation time units\n"

                 // Average wait time.
                 << "Average Wait Time: " << sim_ptr->average_customer_wait_time() << " simulation time units\n"

                 // Maximum wait time.
                 << "Maximum Wait Time: " << sim_ptr->max_customer_wait_time() << " simulation time units\n"

                 // Average line length.
                 << "Average Line Length: " << sim_ptr->average_line_length() << " customers\n"

                 // Maximum line length.
                 << "Maximum Line Length: " << sim_ptr->max_line_length() << " customers\n";

    // Idle times.
    auto idle_times_ptr = sim_ptr->total_servicer_idle_times();

    // Cursor and end.
    auto cursor_it = idle_times_ptr->begin();
    auto end_it = idle_times_ptr->end();

    // Teller idle time.
    for (auto i = 0; cursor_it != end_it; i++)
    {
        // Log.
        file_stream_ << "Servicer #" << i + 1 << " Idle Time: " << *cursor_it << '\n';

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