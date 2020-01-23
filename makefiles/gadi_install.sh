#!/bin/sh

installpath='/scratch/cr78/apps/utility-programs'
mkdir -p $installpath
mkdir -p $installpath/bin/gadi/intel

cd ..
cp -pru  bin/gadi/intel $installpath/bin/gadi
chmod -R g+rx $installpath
chmod -R o+rx $installpath
chmod -R g+rx $installpath/bin/gadi/intel/*.exe
chmod -R o+rx $installpath/bin/gadi/intel/*.exe


