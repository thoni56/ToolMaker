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

ifeq ($(TMARCH),cygwin64)
$(info INFO: Cross-compiling to Cygwin32)
$(info INFO: You need the packages 'cygwin32-gcc-core' (for cross-compiler) and 'cygwin32-w32api-runtime' (for runtime))
$(info INFO: You also need to 'export PATH=/usr/i686-pc-cygwin/sys-root/usr/bin/:$$PATH' to run the binaries)
CC = i686-pc-cygwin-gcc
CFLAGS = -MMD -Wall -g $(INCLUDE) -DTARGETOS=\"$(TMARCH)\"
else
ifeq ($(TMARCH),mingw64)
$(error MINGW64 not supported, build on MINGW32)
endif
CC = gcc
CFLAGS = -MMD -Wall -g $(INCLUDE) -DTARGETOS=\"$(TMARCH)\" $(BITNESS)
endif
