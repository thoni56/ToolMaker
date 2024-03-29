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

ifeq ($(TMARCH),mingw64)
$(error MINGW64 not supported, build on MINGW32)
endif
CC = gcc
CFLAGS = -MMD -Wall -ggdb $(INCLUDE) -DTARGETOS=\"$(TMARCH)\" $(BITNESS)

