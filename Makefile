#Makefile at top of application tree
TOP = .
include $(TOP)/configure/CONFIG
DIRS += $(wildcard *App)
include $(TOP)/configure/RULES_TOP
