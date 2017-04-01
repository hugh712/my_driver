#!/bin/sh
module="cdata"
device="cdata"
mode="777"

insmod ./$module.ko $* || exit 1
