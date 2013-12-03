/*
 * Deamon.cpp
 *
 *  Created on: 3 gru 2013
 *      Author: grzecho
 */

#include "Deamon.h"
#include <cstdlib>
#include <unistd.h> // fork
#include <sys/types.h>  // umask
#include <sys/stat.h>   // umask


Deamon::Deamon() {
    // TODO Auto-generated constructor stub
}

Deamon::~Deamon() {
    // TODO Auto-generated destructor stub
}

void Deamon::demonize() {
    pid_t pid, sid;

   //Fork the Parent Process
    pid = fork();

    if (pid < 0) { exit(EXIT_FAILURE); }

    //We got a good pid, Close the Parent Process
    if (pid > 0) { exit(EXIT_SUCCESS); }

    //Change File Mask
    umask(0);

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0) { exit(EXIT_FAILURE); }

    //Change Directory
    //If we cant find the directory we exit with failure.
    if ((chdir("/")) < 0) { exit(EXIT_FAILURE); }

    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //----------------
    //Main Process
    //----------------
    while(true) {
        //process();    //Run our Process
        sleep(60);    //Sleep for 60 seconds
    }

    //Close the log
//    closelog ();
}
