TOP=../../../..

include $(TOP)/configure/CONFIG

DBDINSTALL = symb.dbd

MYSRCS += devAiSymb.c
MYSRCS += devAoSymb.c
MYSRCS += devBiSymb.c
MYSRCS += devBoSymb.c
MYSRCS += devLiSymb.c
MYSRCS += devLoSymb.c
MYSRCS += devMbbiSymb.c
MYSRCS += devMbbiSymbRaw.c
MYSRCS += devMbboSymb.c
MYSRCS += devMbboSymbRaw.c
MYSRCS += devSiSymb.c
MYSRCS += devSoSymb.c
MYSRCS += devSymbFind.c
MYSRCS += devWfSymb.c

PROD_vxWorks = $(MYSRCS:%.c=%.o)

symb_SRCS = $(MYSRCS)
LIBRARY_vxWorks = symb

include $(TOP)/configure/RULES_BUILD
