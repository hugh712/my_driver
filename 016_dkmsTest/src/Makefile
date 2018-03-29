obj-m := cdata.o
KVERSION := $(shell uname -r)
DEVICE="cdata"
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
