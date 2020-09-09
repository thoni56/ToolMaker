# Common defines for ToolMaker build system

# TODO: generate 'cygwin32' or 'cygwin64' and handle that in all skeleton files too
UNAME = ${shell uname}
TMARCH := ${if ${findstring CYGWIN,$(UNAME)},${if ${findstring WOW, $(UNAME)},cygwin32,cygwin64},${strip ${shell uname}}}

DESTROOT=/usr/local
DESTLIB=$(DESTROOT)/lib/ToolMaker

CC = gcc
CFLAGS = -Wall -g $(INCLUDE) -DTARGETOS=\"$(TMARCH)\"
