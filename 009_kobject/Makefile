obj-m := kobj.o
obj-m += misc_test.o
KVERSION := $(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
load:
	sudo sh load.sh
unload:
	sudo sh unload.sh
clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c
show:
	sudo find /sys -name \*kobj* -o -name \*misc_test*
