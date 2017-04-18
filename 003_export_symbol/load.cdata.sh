#!/bin/sh
module="cdata"
module2="add_sub"
device="cdata"
mode="777"


major=234
echo "major number= $major"

rm -f /dev/${device}

set -o xtrace
mknod /dev/${device} c $major 0
set +o xtrace

insmod $module2/$module2.ko  || exit 1
insmod $module/$module.ko a=2 b=3 AddOrSub=3 || exit 1
ls -l /dev/${device}
