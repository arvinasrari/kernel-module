obj-m += abfunction.o
obj-m += functest_bl.o
obj-m += bl_modifier.o
#obj-m += hook_dest_call.o
obj-m += debug_after.o
obj-m += debug_before.o
#obj-m += crash.o
#obj_m += debug_after.o
#snapshot-objs := main.o memscan.o registers.o  memdump.o utils.o

KDIR := /home/arvin/Desktop/kernel/WIFIFuzz/android-kernels/wahoo/aarm64test/
ccflags-y += -Wno-declaration-after-statement -Werror

PWD := $(shell pwd)
CCPATH := /home/arvin/Desktop/kernel/WIFIFuzz/toolchain/aarch64-linux-android-4.9/bin

default:
	$(MAKE) ARCH=arm64 CROSS_COMPILE=$(CCPATH)/aarch64-linux-android- -C $(KDIR) M="$(PWD)" modules


clean:
	rm -rf *.o *.ko

