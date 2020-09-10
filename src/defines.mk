# Common defines for ToolMaker build system

UNAME = ${shell uname}
ifeq ($(findstring CYGWIN,$(UNAME)),CYGWIN)
  TMARCH := $(if $(findstring WOW,$(UNAME)),WOW),cygwin32,cygwin64)
else
ifeq ($(findstring MINGW,$(UNAME)),MINGW)
  TMARCH := $(if $(findstring 32,$(UNAME)),mingw32,mingw64)
else
ifeq ($(findstring MSYS,$(UNAME)),MSYS)
  TMARCH := msys2
else
  TMARCH := $(UNAME)
endif
endif
endif

DESTROOT=/usr/local
DESTLIB=$(DESTROOT)/lib/ToolMaker

ifeq ($(UNAME),cygwin64))
$(error Cygwin64 not supported, build on Cygwin32)
endif
CC = gcc
CFLAGS = -Wall -g $(INCLUDE) -DTARGETOS=\"$(TMARCH)\" -m32
