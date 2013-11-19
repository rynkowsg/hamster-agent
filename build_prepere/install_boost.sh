#!/bin/bash

# run with su/sudo

wget -O - http://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.gz | tar xz
mv boost_1_55_0 /usr/local/
echo "[ -n \"\$debian_chroot\" ] && BOOST_ROOT=\"/usr/local/boost_1_55_0\"" >> $HOME/.bashrc

cd /usr/local/boost_1_55_0

./bootstrap.sh --prefix=/usr/local --with-libraries=date_time,system,thread
./b2 install        # ./bjam install
