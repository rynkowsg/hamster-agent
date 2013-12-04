/*
 * SignalHandler.cpp
 *
 *  Created on: 5 gru 2013
 *      Author: Grzegorz Rynkowski
 */
#include <csignal>              // signal
#include "SignalHandler.hpp"

bool SignalHandler::mbGotExitSignal = false;

/**
* Default Contructor.
*/
SignalHandler::SignalHandler()
{
}

/**
* Destructor.
*/
SignalHandler::~SignalHandler()
{
}

/**
* Returns the bool flag indicating whether we received an exit signal
* @return Flag indicating shutdown of program
*/
bool SignalHandler::gotExitSignal()
{
    return mbGotExitSignal;
}

/**
* Sets the bool flag indicating whether we received an exit signal
*/
void SignalHandler::setExitSignal(bool _bExitSignal)
{
    mbGotExitSignal = _bExitSignal;
}

/**
* Set up the signal handlers (at least for CTRL-C).
*/
void SignalHandler::setupSignalHandlers(
        std::initializer_list<int> list = {SIGINT})
{
    for(int signal : list) {
        if (std::signal(signal, SignalHandler::handler) == SIG_ERR)
            throw SignalException("Error setting up signal handlers");
    };
}

/**
* Sets exit signal to true.
* @param[in] _ignored Not used but required by function prototype
*                     to match required handler.
*/
void SignalHandler::handler(int signal)
{
    mbGotExitSignal = true;
    switch(signal) {
    case SIGHUP:
        printf("SIGHUP catched!\n");
        //log_message(LOG_FILE,"hangup signal catched");
        break;
    case SIGTERM:
        printf("SIGTERM catched!\n");
        //log_message(LOG_FILE,"terminate signal catched");
        break;
    default:
        printf("catched signal: %d\n", signal);
        break;
    }
}
