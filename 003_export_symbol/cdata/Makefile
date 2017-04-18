obj-m := cdata.o
KVERSION := $(shell uname -r)
SYMBOL_INC = $(obj)/../include
EXTRA_CFLAGS+= -I $(SYMBOL_INC)
KBUILD_EXTRA_SYMBOLS=$(obj)/../add_sub/Module.symvers
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)

#$(info 	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules)
#$(info $(MAKE) $(DEBFLAGS) -C  /lib/modules/$(KVERSION)/build M=$(PWD) modules)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

load:
	sudo sh load.cdata.sh
unload:
	sudo sh unload.cdata.sh
clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c test

