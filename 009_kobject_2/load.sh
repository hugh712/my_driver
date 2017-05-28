#!/bin/sh
module="cdata"
device="cdata"

module2="cdata_plat_dev"
device2="cdata_plat_dev"


insmod ./$module.ko $* || exit 1
lsmod | grep ${device}
sudo find /sys -name "cdata*"

echo ""
echo ""
insmod ./$module2.ko $* || exit 1
lsmod | grep ${device2}
sudo find /sys -name "cdata*"
