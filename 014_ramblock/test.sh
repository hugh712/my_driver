#!/bin/bash

mkfs.ext4 /dev/simp_blkdev
mount /dev/simp_blkdev /tmp/bl/
cp /app/hello.ko ./
df rm -rf /tmp/bl
