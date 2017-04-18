obj-m := add_sub.o 
KVERSION := $(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build
#PWD := $(shell pwd)
PRINT_INC =$(obj)/../include
#PRINT_INC=/home/hugh/mymy/my_driver/003_export_symbol/include
EXTRA_CFLAGS += -I $(PRINT_INC)

default:
	$(info $(PRINT_INC))
	$(MAKE) -I $(PRINT_INC) -C $(KDIR) M=$(PWD) modules

load:
	sudo sh load.cdata.sh
unload:
	sudo sh unload.cdata.sh
clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c test

