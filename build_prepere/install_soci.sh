#!/bin/bash

wget -O - http://downloads.sourceforge.net/project/soci/soci/soci-3.2.2/soci-3.2.2.tar.gz | tar xz
mkdir build
cd build

# adding BOOST_ROOT variable to enable find Boost for cmake
#sed -i '1s/^/set\(BOOST_ROOT \/usr\/local\/boost_1_55_0\)\n\n/' ../soci-3.2.2/cmake/dependencies/Boost.cmake
# change verion of boost
#sed -i 's/Boost\ [0-9].[0-9][0-9].[0-9]/Boost\ 1.55.0/' ../soci-3.2.2/cmake/dependencies/Boost.cmake


cmake -G "Unix Makefiles"   \
    -DWITH_DB2=OFF          \
    -DWITH_FIREBIRD=OFF     \
    -DWITH_MYSQL=OFF        \
    -DWITH_ODBC=OFF         \
    -DWITH_ORACLE=OFF       \
    -DWITH_POSTGRESQL=OFF   \
    -DWITH_SQLITE3=ON       \
    -DWITH_BOOST=ON         \
    ../soci-3.2.2
    #-DBOOST_ROOT="/usr/local/boost_1_55_0" #-DBoost_DEBUG=ON        

make
make install

cd ..
rm -rf build soci-3.2.2
