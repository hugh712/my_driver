#!/bin/sh
module_1="kobj"
module_2="misc_test"
mode="777"


insmod ./$module_1.ko $* || exit 1
insmod ./$module_2.ko $* || exit 1
