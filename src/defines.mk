# Common defines for ToolMaker build system

UNAME = ${shell uname}
TMARCH := ${if ${findstring CYGWIN,$(UNAME)},${if ${findstring WOW, $(UNAME)},cygwin32,cygwin64},${strip ${UNAME}}}

DESTROOT=/usr/local
DESTLIB=$(DESTROOT)/lib/ToolMaker

CC = gcc
CFLAGS = -Wall -g $(INCLUDE) -DTARGETOS=\"$(TMARCH)\" -m32
