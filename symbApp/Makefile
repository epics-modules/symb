TOP=../../../..

include $(TOP)/configure/CONFIG

DBDINSTALL = symb.dbd

SRCS += devAiSymb.c
SRCS += devAoSymb.c
SRCS += devBiSymb.c
SRCS += devBoSymb.c
SRCS += devLiSymb.c
SRCS += devLoSymb.c
SRCS += devMbbiSymb.c
SRCS += devMbbiSymbRaw.c
SRCS += devMbboSymb.c
SRCS += devMbboSymbRaw.c
SRCS += devSiSymb.c
SRCS += devSoSymb.c
SRCS += devSymbFind.c
SRCS += devWfSymb.c

IOC_PROD_vxWorks = $(SRCS:%.c=%.o)
#IOC_LIBRARY_SRCS = $(SRCS)
symb_SRCS = $(SRCS)
IOC_LIBRARY_vxWorks = symb

include $(TOP)/configure/RULES_BUILD
