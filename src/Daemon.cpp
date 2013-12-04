/*
 * Daemon.cpp
 *
 *  Created on: 3 gru 2013
 *      Author: Grzegorz Rynkowski
 */

#include "Daemon.hpp"

#include <csignal>          // signal
#include <cstdio>           // remove
#include <cstdlib>          // exit
#include <cstring>          // strerror
#include <fcntl.h>          // open
#include <unistd.h>         // chdir, close, fork, setsid, sleep, write
#include <stdexcept>        // runtime_error
#include <string>           // to_string
#include <sys/file.h>       // flock
#include <sys/stat.h>       // open, umask
#include <sys/types.h>      // open, umask
#include <syslog.h>         // closelog, openlog, syslog

const std::string Daemon::DEFAULT_DAEMON_NAME = "sample-daemon";
const std::string Daemon::DEFAULT_WORKING_DIR = "/";
const std::string Daemon::DEFAULT_PATH_FOR_FD = "/dev/null";
const std::string Daemon::PIDFILE_DIR         = "/var/run/";
const std::string Daemon::PIDFILE_EXT         = ".pid";
const int Daemon::DEFAULT_SLEEP_SECONDS = 60;

Daemon::Daemon(const std::string& name,
               const std::string& dir,
               const std::string& stdinfile,
               const std::string& stdoutfile,
               const std::string& stderrfile)
        : mName(name),
          mPidfile(PIDFILE_DIR + name + PIDFILE_EXT),
          mDir(dir),
          mPidfilefd(0),
          mInFile(stdinfile),
          mOutFile(stdoutfile),
          mErrFile(stderrfile)
{
    // Call methods related to creating daemon
    create();

    // Register signal handler to handle kill signal
    mSignalHandler.setupSignalHandlers({SIGHUP,SIGINT,SIGQUIT,SIGABRT,SIGTERM});

    // Open a connection to the syslog server
    openlog(mName.c_str(),LOG_NOWAIT|LOG_PID,LOG_USER);

    // Sends a message to the syslog daemon
    syslog(LOG_INFO, "Successfully started daemon\n");
}

Daemon::~Daemon()
{
    destroy();
    syslog(LOG_INFO, "Successfully destroyed daemon\n");
    closelog();
}

void Daemon::create()
{
    createPidfile();
    detachFromParent();
    savePidToPidfile();
    changeWorkingDirectory();
    closeStandardFileDescriptors();
    openNewFileDescriptors();
}

void Daemon::destroy()
{
    destroyPidfile();
}

void Daemon::createPidfile()
{
    // Open or create pidfile
    mPidfilefd = open(mPidfile.c_str(), O_CREAT | O_RDWR, 0666);
    if( -1 == mPidfilefd ) {
        throw DaemonException(std::string(strerror(errno)));
    }
    // Try to lock pidfile
    if( flock(mPidfilefd, LOCK_EX | LOCK_NB) ) {
        // pidfile is locked, it means that another instance is running
        if(EWOULDBLOCK == errno) {
            throw DaemonException(std::string(strerror(errno))
                    .append(": another instance is running"));
        }
        throw DaemonException(std::string(strerror(errno)));
    }
}

void Daemon::detachFromParent()
{
    // Clone ourselves to make a child
    pid_t pid = fork();

    // If the pid is less than zero, something went wrong when forking
    if (pid < 0) {
        throw DaemonException(strerror(errno));
    }
    // If the pid we got back was greater than zero, then the clone was
    // successful and we are the parent
    else if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    // If execution reaches this point we are the child.

    // Because we are a clone of our parent we’ve inherited its umask.
    // Set the umask to zero
    umask(0);

    // Create our own process group
    pid_t sid = setsid();
    if (sid < 0) {
//        syslog(LOG_ERR, "Could not create process group\n");
        throw DaemonException(strerror(errno));
    }

    mPid = sid;
}

void Daemon::savePidToPidfile()
{
    const char* buffer = std::to_string(mPid).append("\n").c_str();
    if (-1 == write(mPidfilefd, buffer, strlen(buffer))) {
        throw DaemonException(strerror(errno));
    }
}

void Daemon::changeWorkingDirectory()
{
    // Change the current working directory
    if (!mDir.empty() && chdir(mDir.c_str()) < 0) {
//        syslog(LOG_ERR, "Could not change working directory to %s\n", mDir);
        throw DaemonException(strerror(errno));
    }
}

void Daemon::closeStandardFileDescriptors()
{
    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void Daemon::openNewFileDescriptors()
{
    // Open standard file descriptors
    int fd0 = open(mInFile.c_str(), O_RDONLY);
    int fd1 = open(mOutFile.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    int fd2 = open(mErrFile.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);

    if (fd0 != STDIN_FILENO || fd1 != STDOUT_FILENO || fd2 != STDERR_FILENO)  {
        //Unexpected file descriptors
        throw DaemonException("standard file descriptors were not opened as expected");
    }
}

void Daemon::destroyPidfile()
{
    // Unlock pidfile
    if( -1 == flock(mPidfilefd, LOCK_UN) ) {
        throw DaemonException(std::string(strerror(errno)));
    }
    // Remove pidfile
    if( -1 == remove(mPidfile.c_str()) ) {
        throw DaemonException(std::string(strerror(errno)));
    }
}

void Daemon::demonize(void (*process)(), int sleep_seconds)
{
    while(!mSignalHandler.gotExitSignal()) {
        // staff to do
        if (process) process();
        sleep(sleep_seconds);
    }
}

void Daemon::demonize(void (*process)(bool (*)(), int), int sleep_seconds)
{
        if (process) process(mSignalHandler.gotExitSignal, sleep_seconds);
}
