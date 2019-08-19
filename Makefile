ifeq ($(KERNELRELEASE),)
PWD = $(shell pwd)
#KERNEL_DIR = /home/yuan/linux/linux-3.16.2
KERNEL_DIR = /root/linux-3.5
modules:
	make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
else
obj-m += driver_app.o                                                      
endif
