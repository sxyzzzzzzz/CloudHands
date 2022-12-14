include ../make.include
DPDK=/usr/local/dpdk/dpdk_src
DPDK_FLAGS=$(shell cat ${DPDK}/include/cflags.txt)
DPDK_LIB_FLAGS = $(shell cat ${DPDK}/lib/ldflags.txt)
CFLAGS  = ${BUILD_CFLAGS}  -O0 -rdynamic -D_GNU_SOURCE -DUSE_DPDK ${DPDK_FLAGS} -pthread
CFLAGS += -I../lib/common  -I../lib/shm -I../lib/thread -I../lib/ptables -I../packet -I../MProcess -I../statistic
CFLAGS += -I../rule -I../filter
CFLAGS += -I${DPDK}/include -include ${DPDK}/include/rte_config.h

LDFLAGS  = ${BUILD_LDFLAGS} ${DPDK_LIB_FLAGS} -lpthread -lcjson

common_package = ../lib/common/*.o
cpool_package = ../lib/thread/*.o
shm_package = ../lib/shm/*.o
ptables_package = ../lib/ptables/*.o
pkt_package = ../packet/*.o
mprocess_package = ../MProcess/*.o
stat_package = ../statistic/*.o
rule_package = ../rule/*.o
filter_package = ../filter/*.o

pdis_package= PDispatcher

pdis_SOURCES = PDispatcher.c \
			   ch_pdispatcher_context.c \
			   ch_packet_rxtask.c\
			   ch_port_context.c \
			   ch_port_pool.c \
			   ch_packet_rxtask_pool.c

pdis_OBJECTS =$(patsubst %.c,%.o,$(pdis_SOURCES))
pdis_DEPENDS =$(patsubst %.c,%.d,$(pdis_SOURCES))
pdis_ASMFILE =$(patsubst %.c,%.s,$(pdis_SOURCES))

quiet_cmd_dpdk = LINK   $@ 
	cmd_pdis = ${CC} ${CFLAGS} -o $@ $(pdis_OBJECTS)  \
				   $(common_package) $(cpool_package) $(shm_package) $(ptables_package)\
				   $(pkt_package) $(mprocess_package) $(stat_package) $(rule_package) $(filter_package)\
				   $(LDFLAGS)

.PHONY: all clean

all: $(pdis_package)

$(pdis_package): $(pdis_OBJECTS) 
	$(call cmd,pdis)
-include $(pdis_DEPENDS)

$(common_package):
	$(call,make)

$(shm_package):
	$(call,make)

$(thread_package):
	$(call,make)

$(ptables_package):
	$(call,make)

$(pkt_package):
	$(call,make)

$(mprocess_package):
	$(call,make)

$(stat_package):
	$(call,make)

$(rule_package):
	$(call,make)

$(filter_package):
	$(call,make)

clean:
	@rm -rf $(pdis_OBJECTS) $(pdis_DEPENDS) $(pdis_ASMFILE) $(pdis_package)


