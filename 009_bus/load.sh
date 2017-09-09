#!/bin/sh
module_1="mybus"


insmod ./$module_1.ko $* || exit 1
