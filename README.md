# hamster-agent

This project provides a daemon that communicates with hamster-service daemon.  
In other words it is a connector between Hamster Time Tracker and mobile thin client which de facto I'm also going to create.

##File structure
```
build/                              # Directory to build files (*)

cmake/                              # CMake files
    cmake_uninstall.cmake.in  
    Modules/  
        FindDBusCpp.cmake  
        FindMsgPack.cmake  
  
resources/                          # Misc resources
    create-dbus-proxy-header.sh  
    script-initd.sh.in  

source/                             # Sources directory
    CMakeLists.txt  
    config.h.in  
    Daemon.cpp  
    Daemon.hpp  
    Data.cpp  
    Data.h  
    Hamster_proxy.hpp  
    main.cpp  
    Parser.h  
    ParserXML.cpp  
    ParserXML.h  
    SignalHandler.cpp  
    SignalHandler.hpp  
    Storage.cpp  
    Storage.h  
```

(*) = the command line tool creates files in these folders


##Required to build

###1. Hamster

###2. CMake

```
apt-get install cmake
```

###3. Libraries
* Boost
    * date-time
    * filesystem
    * system
* MsgPack
* D-Bus-C++ library

To install:  
```
apt-get install libboost-date-time-dev libboost-filesystem-dev
                libboost-system-dev libmsgpack-dev  libdbus-c++-dev
```

###4. Tools

- **qdbus**  
Tool that provides information about dbus services that are running and ability to manipulate them. I use it to get D-Bus XML introspection document of Hamster.  
To install: &nbsp;```apt-get install qdbus```

- **libdbus-c++-bin**  
It contains `dbusxx-xml2cpp` that can generate proxy and adapter interfaces from modified D-Bus XML introspection documents.  
To install: &nbsp;```apt-get install libdbus-c++-bin```


##Installation

```
cd build  
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug"..
make
sudo make install
```

##Uninstallation

Uninstalling process is based on build/install_manifest.txt file. This files is generated during the installation. So it works only if `make install` was entered before.
```
sudo make uninstall
```

##How to use

Access to daemon is provided by init.d script.  
Usage:
```/etc/init.d/hamster-agent {start|stop|status|restart|force-reload}```

To start:    ```sudo service hamster-agent start```  
To stop:     ```sudo service hamster-agent stop```  
To restart:  ```sudo service hamster-agent restart```  

## License
Hamster Agent has an GNU GPLv3 license. See the LICENSE file for more information.
