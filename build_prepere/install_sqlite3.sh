#!/bin/bash
wget -O - http://www.sqlite.org/2013/sqlite-autoconf-3080100.tar.gz | tar xz
cd sqlite-autoconf-3080100
./configure --prefix=/usr/local/bin/
make
sudo make install
rm -rf sqlite-autoconf-3080100

