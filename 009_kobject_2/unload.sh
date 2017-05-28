#!/bin/sh
module="cdata"
device="cdata"

module2="cdata_plat_dev"
device2="cdata_plat_dev"


# invoke rmmod with all arguments we got
/sbin/rmmod $module $* || exit 1
/sbin/rmmod $module2 $* || exit 1

# Remove stale nodes

rm -f /dev/${device} /dev/${device}

