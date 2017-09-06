#!/bin/sh
module_1="block"

# invoke rmmod with all arguments we got
/sbin/rmmod $module_1 $* || exit 1

