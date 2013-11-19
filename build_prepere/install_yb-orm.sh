#!/bin/bash


#http://soci.sourceforge.net/doc/3.2/installation.html
DEPS=(  "libxml2-dev:2.6.31"
        "libcppunit-dev:1.12.0"
        "autoconf:2.61"
        "automake:1.10.1"
        "libqt4-dev:4.5"
        "libwxgtk2.8-dev:2.8.12"
        "unixodbc-dev:2.2.14"
        "instantclient:10.2"
        "libmyodbc:5.1.10"
        "odbc-postgresql:09.00.0310" )

#libboost-thread-dev:1.34.1     # ./install_boost.sh
#libboost-date-time-dev:1.34.1
#libsqlite3-dev:3.7.9           # ./install_sqlite3.sh
#soci:3.2.0                     # ./install_soci.h

for dep in "${DEPS[@]}" ; do
    PKG=${dep%%:*}
    VER=${dep#*:}
    
    version=$(dpkg-query -W -f='${Version} \n' $PKG  2> /dev/null)
    if dpkg --compare-versions "$version" '<' $VER; then
        echo "installing $PKG..."
        sudo apt-get install $PKG
    else
        echo "$PKG is installed in version $version"
    fi
    echo
done


wget -O - https://yb-orm.googlecode.com/files/yborm-0.4.0.tar.gz | tar xz

mkdir build
cd build

cmake -G "Unix Makefiles" ../yborm-0.4.0/

make
sudo make install

cd ..
rm -rf build yborm-0.4.0

