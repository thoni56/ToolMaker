# Common defines for ToolMaker build system

UNAME = $(shell uname)
ifeq ($(findstring CYGWIN,$(UNAME)),CYGWIN)
  ifeq ($(findstring WOW,$(UNAME)),WOW)
	TMARCH := cygwin32
  else
	TMARCH := cygwin64
  endif
else
  ifeq ($(findstring MINGW,$(UNAME)),MINGW)
	ifeq ($(findstring 32,$(UNAME)),32)
	  TMARCH := mingw32
	else
	  TMARCH := mingw64
	endif
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
