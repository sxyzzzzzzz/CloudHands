##########################################################
#Copyright(C) 2012 WAF PROJECT TEAM
#Author(A) shajianfeng
##########################################################

include ../../../make.include
DPDK=/usr/local/dpdk/dpdk_src
DPDK_FLAGS=$(shell cat ${DPDK}/include/cflags.txt)
CFLAGS  = ${BUILD_CFLAGS}  -O0 -rdynamic -D_GNU_SOURCE -DUSE_DPDK ${DPDK_FLAGS}
CFLAGS += -I../../../lib/common -I../../../packet -I../../../lib/ptables -I../../../lib/shm -I../../../lib/fstore
CFLAGS += -I../../../lib/thread -I../../../MProcess -I../../../rule -I../../../filter
CFLAGS += -I../ -I../../ -I${DPDK}/include -include ${DPDK}/include/rte_config.h
CFLAGS +=  -fPIC

ch_ssh_SOURCES = ch_ssh.c \
				  ch_ssh_session_entry.c 

ch_ssh_OBJECTS = $(patsubst %.c,%.o,$(ch_ssh_SOURCES))
ch_ssh_DEPENDS = $(patsubst %.c,%.d,$(ch_ssh_SOURCES))
ch_ssh_ASMFILE = $(patsubst %.c,%.s,$(ch_ssh_SOURCES))

.PHONY: all clean

all: $(ch_ssh_OBJECTS)

clean:
	@rm -fr $(ch_ssh_OBJECTS) $(ch_ssh_DEPENDS) $(ch_ssh_ASMFILE) $(ch_ssh_package)
	@rm -fr *.d *.o *.s 

