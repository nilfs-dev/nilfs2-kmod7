
ifndef CONFIG_NILFS2_FS
  EXTERNAL_BUILD=y
  CONFIG_NILFS2_FS=m
  # Uncomment below to do debug build.
  #CONFIG_NILFS_DEBUG=y
endif

obj-$(CONFIG_NILFS2_FS) += nilfs2.o
nilfs2-y := inode.o file.o dir.o super.o namei.o page.o mdt.o \
	btnode.o bmap.o btree.o direct.o dat.o recovery.o \
	the_nilfs.o segbuf.o segment.o cpfile.o sufile.o \
	ifile.o alloc.o gcinode.o ioctl.o


list-$(CONFIG_NILFS2_FS) += nilfs2

# Some assembler options.
ifneq ($(CONFIG_NILFS_DEBUG),)
  KBUILD_CFLAGS += -g -fno-omit-frame-pointer
endif

KVER := $(shell uname -r)
KSRC := /lib/modules/$(KVER)/build

USERINCLUDE += -I../../include/uapi
LINUXINCLUDE += -I../../include

# RHEL release number
_SEDCMD := '/^RHEL_RELEASE\s*=\s*[0-9]+/{s/^[^=]+=\s*([0-9]+).*$$/\1/;p;q;}'
RHEL_RELEASE_N := $(shell sed -nE $(_SEDCMD) $(KSRC)/Makefile)

ifneq ($(RHEL_RELEASE_N),)
  KBUILD_CFLAGS += -D RHEL_RELEASE_N=$(RHEL_RELEASE_N)
endif

#
# Only support external build, and does not support kernel build.
#
ifneq ($(KERNELRELEASE),)

ifeq ($(EXTERNAL_BUILD),y)
  KBUILD_CFLAGS += -U CONFIG_NILFS_XATTR       # not supported yet
  KBUILD_CFLAGS += -U CONFIG_NILFS_POSIX_ACL   # not supported yet

  ifneq ($(CONFIG_NILFS_DEBUG),)
    KBUILD_CFLAGS += -D CONFIG_NILFS_DEBUG
  endif
endif

else  # KERNELRELEASE

#
# Description for external build begins here
#

MDIR := /lib/modules/$(KVER)/kernel/fs/nilfs2/
PWD := $(shell pwd)

KBUILD_EXTMOD := $(PWD)
export KBUILD_EXTMOD

PREINC := -I$(PWD)/../../include -I$(PWD)/../../include/uapi
CFLAGS += -Wall

default:
	$(MAKE) -C $(KSRC) NOSTDINC_FLAGS="$(PREINC)" modules

install: unload
	install -d $(MDIR)
	install -m 644 -c $(addsuffix .ko,$(list-m)) $(MDIR)
	/sbin/depmod $(KVER) -A

uninstall: unload
	rm -rf $(addprefix $(MDIR),$(addsuffix .ko,$(list-m)))
	/sbin/depmod $(KVER) -A

load:
	modprobe $(list-m)

unload:
	@test "`uname -r`" != "$(KVER)" || \
	     if [ -n "`mount -t $(list-m)`" ]; then \
	         echo "Unmount $(list-m) first."; false; \
	     elif (/sbin/lsmod | grep -e ^$(list-m)' ') > /dev/null; then /sbin/rmmod $(list-m); \
	     	 if [ $$? != 0 ]; then echo "failed to unload $(list-m)"; false; \
	         else echo "unloaded $(list-m)"; fi \
	     fi \

clean:
	rm -f *.mod.c *.mod *.o *.ko .*.cmd .*.flags *.lst *~ .#*
	rm -f modules.order Module.symvers
	rm -rf .tmp_versions .$(obj-m:.o=)*

endif  # End of KERNELRELEASE
