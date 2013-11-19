#!/bin/bash

wget -O - http://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.gz | tar xz
#mv boost_1_55_0 /usr/local/
echo "[ -n \"\$debian_chroot\" ] && BOOST_ROOT=\"/usr/local/boost_1_55_0\"" >> $HOME/.bashrc

#cd /usr/local/boost_1_55_0

./bootstrap.sh #--prefix=/usr/local #--with-libraries=date_time,system,thread
sudo ./b2 install -j 8

#with using c++11:
#http://hnrkptrsn.github.io/2013/02/26/c11-and-boost-setup-guide/
