#!/bin/sh
module_1="myNotifier"


insmod ./$module_1.ko $* || exit 1
