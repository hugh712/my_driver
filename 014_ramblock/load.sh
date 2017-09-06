#!/bin/sh
module_1="block"


insmod ./$module_1.ko $* || exit 1
