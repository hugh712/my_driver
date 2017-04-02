#!/bin/sh
module="cdata"
device="cdata"

# invoke rmmod with all arguments we got
/sbin/rmmod $module $* || exit 1

