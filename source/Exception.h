/*
 * Exception.h
 *
 *  Created on: 18.09.2014
 *      Author: Grzegorz Rynkowski
 *              grzegorz.rynkowski@gmail.com
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>        // runtime_error
#include <string>           // string
#include <syslog.h>         // syslog

#define DefineException(Name, Base)                                 \
    class Name : public Base                                        \
    {                                                               \
    public:                                                         \
        Name(const std::string& _message) : Base(_message)          \
        {                                                           \
            syslog(LOG_ERR, "%s: %s", #Name, _message.c_str());     \
        }                                                           \
    };

#endif // EXCEPTION_H
