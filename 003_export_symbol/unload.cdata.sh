#!/bin/sh
module="cdata"
module2="add_sub"
device="cdata"

# invoke rmmod with all arguments we got
/sbin/rmmod $module $* || exit 1
/sbin/rmmod $module2 $* || exit 1

