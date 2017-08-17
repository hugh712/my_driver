#!/bin/sh
module_1="kernel_thread"


insmod ./$module_1.ko $* || exit 1
