#!/bin/bash -ev

sudo apt-get update -qq
sudo apt-get upgrade -y -qq
sudo apt-get install -y -qq build-essential libqt4-dev qt5-qmake cmake qttools5-dev libqt5webkit5-dev qttools5-dev-tools
sudo apt-get install -y -qq qt5-default python-sphinx texlive-latex-base inotify-tools openssl libssl-dev libdb++-dev 
sudo apt-get install -y -qq libminiupnpc-dev git sqlite3 libsqlite3-dev g++ libpng-dev git g++ gedit python make libbz2-dev 
sudo apt-get install -y -qq libdb++-dev libdb-dev libssl-dev openssl libreadline-dev autoconf libtool git libleveldb-dev 
sudo apt-get install -y -qq libblkid-dev e2fslibs-dev libboost-all-dev libaudit-dev
