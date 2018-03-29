obj-m := cdata.o
KVERSION := $(shell uname -r)
DEVICE="cdata"
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)/src

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
test:
	gcc -o test test.c
load:
	sudo sh load.cdata.sh
unload:
	sudo sh unload.cdata.sh
clean:
	rm -rf src/*.o src/*.ko src/.*cmd src/modules.* src/Module.* src/.tmp_src/versions src/*.mod.c test test2
show:
	ls -l /dev/$(DEVICE); lsmod | grep $(DEVICE)
