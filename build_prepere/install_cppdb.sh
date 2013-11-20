#!/bin/bash

wget -O - http://downloads.sourceforge.net/project/cppcms/cppdb/0.3.1/cppdb-0.3.1.tar.bz2 | tar xj
mkdir build
cd build


cmake -G "Unix Makefiles"               \
    -D CMAKE_INSTALL_PREFIX=/usr/local  \
    -D LIBDIR=lib64                     \
    -D DISABLE_SQLITE=OFF               \
    -D SQLITE_BACKEND_INTERNAL=OFF      \
    -D DISABLE_MYSQL=ON                 \
    -D MYSQL_BACKEND_INTERNAL=ON        \
    -D DISABLE_PQ=ON                    \
    -D PQ_BACKEND_INTERNAL=ON           \
    -D DISABLE_ODBC=ON                  \
    -D ODBC_BACKEND_INTERNAL=ON         \
    ../cppdb-0.3.1

make
make install

cd ..
rm -rf build cppdb-0.3.1
