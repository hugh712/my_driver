#!/bin/bash

#create and copy nessesary files
sudo mkdir /usr/src/cdata-1.0
sudo cp  -rf  dkms.conf src /usr/src/cdata-1.0/

#dkms add module
sudo dkms add -m cdata -v 1.0

#dkms build module
sudo dkms build -m cdata -v 1.0

#dkms install module
sudo dkms install -m cdata -v 1.0

# make test program


