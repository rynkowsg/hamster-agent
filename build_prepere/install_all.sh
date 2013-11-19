#!/bin/bash
./install_sqlite3.sh
./install_boost.sh
#./install_soci.sh

#Reload the list of system-wide library paths
ldconfig #-v
