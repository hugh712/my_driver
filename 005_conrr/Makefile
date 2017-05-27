obj-m := cdata.o

KVERSION := $(shell uname -r)

KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
test:
	gcc -o test test.c
load:
	sudo sh cdata.load.sh
unload:
	sudo sh cdata.unload.sh
clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c test
