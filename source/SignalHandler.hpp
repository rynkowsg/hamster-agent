/*
 * SignalHandler.hpp
 *
 *  Created on: 5 gru 2013
 *      Author: Grzegorz Rynkowski
 */

#ifndef SIGNALHANDLER_HPP_
#define SIGNALHANDLER_HPP_

#include <initializer_list> // initializer_list

class SignalHandler
{
public:
    SignalHandler();
    ~SignalHandler();

    static bool gotExitSignal();
    static void setExitSignal(bool _bExitSignal);
    void setupSignalHandlers(std::initializer_list<int> list);

protected:
    static void handler(int signal);

    static bool mbGotExitSignal;
};

#endif /* SIGNALHANDLER_HPP_ */
