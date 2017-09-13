#!/bin/sh
module_1="myblock"


insmod ./$module_1.ko $* || exit 1
