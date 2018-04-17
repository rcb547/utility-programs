#!/bin/sh


installpath='/short/public/rcb547/apps/utility-programs'
mkdir -p $installpath
mkdir -p $installpath/bin/raijin/intel

cd ..
cp -pru  bin/raijin/intel $installpath/bin/raijin
chmod -R g+rx $installpath
chmod -R o+rx $installpath
chmod -R g+rx $installpath/bin/raijin/intel/*.exe
chmod -R o+rx $installpath/bin/raijin/intel/*.exe


