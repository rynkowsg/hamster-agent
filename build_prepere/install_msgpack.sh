#!/bin/bash

target=msgpack-0.5.4
wget -O - http://downloads.sourceforge.net/project/msgpack/msgpack/cpp/$target.tar.gz | tar xz
cd $target

./configure
make -j8
sudo make install

cd ..
rm -rf $target
sudo ldconfig
