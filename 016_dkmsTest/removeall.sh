#!/bin/bash

MODULE=cdata
VERSION=1.0

make clean

sudo ./unload.cdata.sh

#create and copy nessesary files

if [ -e "/usr/src/${MODULE}-${VERSION}" ]; then
    sudo rm -rf /usr/src/${MODULE}-${VERSION}
fi


sudo dkms remove ${MODULE}/${$VERSION} --all

