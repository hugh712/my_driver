#!/bin/sh
module_1="kobj"
module_2="misc_test"

# invoke rmmod with all arguments we got
/sbin/rmmod $module_1 $* || exit 1
/sbin/rmmod $module_2 $* || exit 1

