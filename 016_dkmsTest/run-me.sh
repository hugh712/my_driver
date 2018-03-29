#!/bin/bash

set -e

MODULE=cdata
VERSION=1.0

#create and copy nessesary files

if [ -e "/usr/src/${MODULE}-${VERSION}" ]; then
	sudo rm -rf /usr/src/${MODULE}-${VERSION}
fi

sudo mkdir /usr/src/${MODULE}-${VERSION}
sudo cp  -rf  dkms.conf src /usr/src/${MODULE}-${VERSION}/

#dkms add module
sudo dkms add -m ${MODULE} -v ${VERSION}

#dkms build module
sudo dkms build -m ${MODULE} -v ${VERSION}

#dkms install module
sudo dkms install -m ${MODULE} -v ${VERSION}

# make test program
make test

# insert module
sudo modprobe ${MODULE}
sudo ./load.cdata.sh

# show module
lsmod | grep ${MODULE}
ll /dev/${MODULE}

# run user space test program
./test
