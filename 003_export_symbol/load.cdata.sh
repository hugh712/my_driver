#!/bin/sh
module="cdata"
module2="add_sub"
device="cdata"
mode="777"

insmod ./$module2.ko $* || exit 1
insmod ./$module.ko a=3 b=2 AddOrSub=2 || exit 1
