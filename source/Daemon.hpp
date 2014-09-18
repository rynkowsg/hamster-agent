/*
 * Daemon.hpp
 *
 *  Created on: 3 gru 2013
 *      Author: Grzegorz Rynkowski
 */

#ifndef DAEMON_HPP_
#define DAEMON_HPP_

#include <string>
#include "SignalHandler.hpp"

class Daemon
{
public:
    Daemon(const std::string& name = DEFAULT_DAEMON_NAME,
           const std::string& dir = DEFAULT_WORKING_DIR,
           const std::string& stdinfile = DEFAULT_PATH_FOR_FD,
           const std::string& stdoutfile = DEFAULT_PATH_FOR_FD,
           const std::string& stderrfile = DEFAULT_PATH_FOR_FD);
    virtual ~Daemon();
    void demonize(void (*process)(), int sleep_seconds = DEFAULT_SLEEP_SECONDS);
    void demonize(void (*process)(bool (*)(), int), int sleep_seconds = DEFAULT_SLEEP_SECONDS);

private:
    inline void create();
    inline void destroy();
    void createPidfile();
    void detachFromParent();
    void savePidToPidfile();
    void changeWorkingDirectory();
    void closeStandardFileDescriptors();
    void openNewFileDescriptors();
    void destroyPidfile();

    void handleSignals();

public:
    const static std::string DEFAULT_DAEMON_NAME;
    const static std::string DEFAULT_WORKING_DIR;
    const static std::string DEFAULT_PATH_FOR_FD;
    const static std::string PIDFILE_DIR;
    const static std::string PIDFILE_EXT;
    const static int DEFAULT_SLEEP_SECONDS;

private:
    std::string mName;
    pid_t mPid;
    std::string mPidfile;
    std::string mDir;
    int mPidfilefd;
    SignalHandler mSignalHandler;
    std::string mInFile, mOutFile, mErrFile;
};

#endif /* DAEMON_HPP_ */
