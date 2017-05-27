#!/bin/sh
module="cdata"
device="cdata"

# invoke rmmod with all arguments we got
sudo /sbin/rmmod $module $* || exit 1


# Remove stale nodes

sudo rm -f /dev/${device} /dev/${device}

