# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=smk - Win32 Test
!MESSAGE No configuration specified.  Defaulting to smk - Win32 Test.
!ENDIF

!IF "$(CFG)" != "smk - Win32 Release" && "$(CFG)" != "smk - Win32 Debug" &&\
 "$(CFG)" != "smk - Win32 Test" && "$(CFG)" != "smk - Win32 AMOS"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE
!MESSAGE NMAKE /f "smk.mak" CFG="smk - Win32 Test"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "smk - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "smk - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "smk - Win32 Test" (based on "Win32 (x86) Console Application")
!MESSAGE "smk - Win32 AMOS" (based on "Win32 (x86) Console Application")
!MESSAGE
!ERROR An invalid configuration is specified.
!ENDIF

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
################################################################################
# Begin Project
# PROP Target_Last_Scanned "smk - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "smk - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\smk.exe"

CLEAN :
	-@erase "$(INTDIR)\action.obj"
	-@erase "$(INTDIR)\ast.obj"
	-@erase "$(INTDIR)\char.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\definition.obj"
	-@erase "$(INTDIR)\dfa.obj"
	-@erase "$(INTDIR)\lmprintf.obj"
	-@erase "$(INTDIR)\lookahead.obj"
	-@erase "$(INTDIR)\map.obj"
	-@erase "$(INTDIR)\name.obj"
	-@erase "$(INTDIR)\nfa.obj"
	-@erase "$(INTDIR)\nfas.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\rule.obj"
	-@erase "$(INTDIR)\scanner.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\smalloc.obj"
	-@erase "$(INTDIR)\smk.obj"
	-@erase "$(INTDIR)\smkErr.obj"
	-@erase "$(INTDIR)\smkList.obj"
	-@erase "$(INTDIR)\smkParse.obj"
	-@erase "$(INTDIR)\smkPaSema.obj"
	-@erase "$(INTDIR)\smkScan.obj"
	-@erase "$(INTDIR)\smkScSema.obj"
	-@erase "$(INTDIR)\time.obj"
	-@erase "$(INTDIR)\token.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(INTDIR)\vocabulary.obj"
	-@erase "$(INTDIR)\write.obj"
	-@erase "$(OUTDIR)\smk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\tmk" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\license" /I "..\tmk" /I "..\imp" /D\
 "NDEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/smk.pch" /YX /Fo"$(INTDIR)/" /c\

CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/smk.bsc"
BSC32_SBRS= \

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/smk.pdb" /machine:I386\
 /out:"$(OUTDIR)/smk.exe"
LINK32_OBJS= \
	"$(INTDIR)\action.obj" \
	"$(INTDIR)\ast.obj" \
	"$(INTDIR)\char.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\definition.obj" \
	"$(INTDIR)\dfa.obj" \
	"$(INTDIR)\lmprintf.obj" \
	"$(INTDIR)\lookahead.obj" \
	"$(INTDIR)\map.obj" \
	"$(INTDIR)\name.obj" \
	"$(INTDIR)\nfa.obj" \
	"$(INTDIR)\nfas.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\rule.obj" \
	"$(INTDIR)\scanner.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\smalloc.obj" \
	"$(INTDIR)\smk.obj" \
	"$(INTDIR)\smkErr.obj" \
	"$(INTDIR)\smkList.obj" \
	"$(INTDIR)\smkParse.obj" \
	"$(INTDIR)\smkPaSema.obj" \
	"$(INTDIR)\smkScan.obj" \
	"$(INTDIR)\smkScSema.obj" \
	"$(INTDIR)\time.obj" \
	"$(INTDIR)\token.obj" \
	"$(INTDIR)\version.obj" \
	"$(INTDIR)\vocabulary.obj" \
	"$(INTDIR)\write.obj"

"$(OUTDIR)\smk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\smk.exe"

CLEAN :
	-@erase "$(INTDIR)\action.obj"
	-@erase "$(INTDIR)\ast.obj"
	-@erase "$(INTDIR)\char.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\definition.obj"
	-@erase "$(INTDIR)\dfa.obj"
	-@erase "$(INTDIR)\lmprintf.obj"
	-@erase "$(INTDIR)\lookahead.obj"
	-@erase "$(INTDIR)\map.obj"
	-@erase "$(INTDIR)\name.obj"
	-@erase "$(INTDIR)\nfa.obj"
	-@erase "$(INTDIR)\nfas.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\rule.obj"
	-@erase "$(INTDIR)\scanner.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\smalloc.obj"
	-@erase "$(INTDIR)\smk.obj"
	-@erase "$(INTDIR)\smkErr.obj"
	-@erase "$(INTDIR)\smkList.obj"
	-@erase "$(INTDIR)\smkParse.obj"
	-@erase "$(INTDIR)\smkPaSema.obj"
	-@erase "$(INTDIR)\smkScan.obj"
	-@erase "$(INTDIR)\smkScSema.obj"
	-@erase "$(INTDIR)\time.obj"
	-@erase "$(INTDIR)\token.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(INTDIR)\vocabulary.obj"
	-@erase "$(INTDIR)\write.obj"
	-@erase "$(OUTDIR)\smk.exe"
	-@erase "$(OUTDIR)\smk.ilk"
	-@erase "$(OUTDIR)\smk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\tmk" /I "..\imp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\tmk" /I\
 "..\imp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/smk.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/smk.bsc"
BSC32_SBRS= \

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/smk.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/smk.exe"
LINK32_OBJS= \
	"$(INTDIR)\action.obj" \
	"$(INTDIR)\ast.obj" \
	"$(INTDIR)\char.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\definition.obj" \
	"$(INTDIR)\dfa.obj" \
	"$(INTDIR)\lmprintf.obj" \
	"$(INTDIR)\lookahead.obj" \
	"$(INTDIR)\map.obj" \
	"$(INTDIR)\name.obj" \
	"$(INTDIR)\nfa.obj" \
	"$(INTDIR)\nfas.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\rule.obj" \
	"$(INTDIR)\scanner.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\smalloc.obj" \
	"$(INTDIR)\smk.obj" \
	"$(INTDIR)\smkErr.obj" \
	"$(INTDIR)\smkList.obj" \
	"$(INTDIR)\smkParse.obj" \
	"$(INTDIR)\smkPaSema.obj" \
	"$(INTDIR)\smkScan.obj" \
	"$(INTDIR)\smkScSema.obj" \
	"$(INTDIR)\time.obj" \
	"$(INTDIR)\token.obj" \
	"$(INTDIR)\version.obj" \
	"$(INTDIR)\vocabulary.obj" \
	"$(INTDIR)\write.obj"

"$(OUTDIR)\smk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "smk - Win32 Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "smk___Wi"
# PROP BASE Intermediate_Dir "smk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\smk.exe"

CLEAN :
	-@erase "$(INTDIR)\action.obj"
	-@erase "$(INTDIR)\ast.obj"
	-@erase "$(INTDIR)\char.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\definition.obj"
	-@erase "$(INTDIR)\dfa.obj"
	-@erase "$(INTDIR)\lmprintf.obj"
	-@erase "$(INTDIR)\lookahead.obj"
	-@erase "$(INTDIR)\map.obj"
	-@erase "$(INTDIR)\name.obj"
	-@erase "$(INTDIR)\nfa.obj"
	-@erase "$(INTDIR)\nfas.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\rule.obj"
	-@erase "$(INTDIR)\scanner.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\smalloc.obj"
	-@erase "$(INTDIR)\smk.obj"
	-@erase "$(INTDIR)\smkErr.obj"
	-@erase "$(INTDIR)\smkList.obj"
	-@erase "$(INTDIR)\smkParse.obj"
	-@erase "$(INTDIR)\smkPaSema.obj"
	-@erase "$(INTDIR)\smkScan.obj"
	-@erase "$(INTDIR)\smkScSema.obj"
	-@erase "$(INTDIR)\time.obj"
	-@erase "$(INTDIR)\token.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(INTDIR)\vocabulary.obj"
	-@erase "$(INTDIR)\write.obj"
	-@erase "$(OUTDIR)\smk.exe"
	-@erase "$(OUTDIR)\smk.ilk"
	-@erase "$(OUTDIR)\smk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\tmk" /I "..\imp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\tmk" /I "..\imp" /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\tmk" /I\
 "..\imp" /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/smk.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/smk.bsc"
BSC32_SBRS= \

LINK32=link.exe
# ADD BASE LINK32 ..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/smk.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/smk.exe"
LINK32_OBJS= \
	"$(INTDIR)\action.obj" \
	"$(INTDIR)\ast.obj" \
	"$(INTDIR)\char.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\definition.obj" \
	"$(INTDIR)\dfa.obj" \
	"$(INTDIR)\lmprintf.obj" \
	"$(INTDIR)\lookahead.obj" \
	"$(INTDIR)\map.obj" \
	"$(INTDIR)\name.obj" \
	"$(INTDIR)\nfa.obj" \
	"$(INTDIR)\nfas.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\rule.obj" \
	"$(INTDIR)\scanner.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\smalloc.obj" \
	"$(INTDIR)\smk.obj" \
	"$(INTDIR)\smkErr.obj" \
	"$(INTDIR)\smkList.obj" \
	"$(INTDIR)\smkParse.obj" \
	"$(INTDIR)\smkPaSema.obj" \
	"$(INTDIR)\smkScan.obj" \
	"$(INTDIR)\smkScSema.obj" \
	"$(INTDIR)\time.obj" \
	"$(INTDIR)\token.obj" \
	"$(INTDIR)\version.obj" \
	"$(INTDIR)\vocabulary.obj" \
	"$(INTDIR)\write.obj"

"$(OUTDIR)\smk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "smk___Wi"
# PROP BASE Intermediate_Dir "smk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "smk___Wi"
# PROP Intermediate_Dir "smk___Wi"
# PROP Target_Dir ""
OUTDIR=.\smk___Wi
INTDIR=.\smk___Wi

ALL : ".\smk.exe"

CLEAN :
	-@erase "$(INTDIR)\action.obj"
	-@erase "$(INTDIR)\ast.obj"
	-@erase "$(INTDIR)\char.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\definition.obj"
	-@erase "$(INTDIR)\dfa.obj"
	-@erase "$(INTDIR)\lmprintf.obj"
	-@erase "$(INTDIR)\lookahead.obj"
	-@erase "$(INTDIR)\map.obj"
	-@erase "$(INTDIR)\name.obj"
	-@erase "$(INTDIR)\nfa.obj"
	-@erase "$(INTDIR)\nfas.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\rule.obj"
	-@erase "$(INTDIR)\scanner.obj"
	-@erase "$(INTDIR)\screen.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\smalloc.obj"
	-@erase "$(INTDIR)\smk.obj"
	-@erase "$(INTDIR)\smkErr.obj"
	-@erase "$(INTDIR)\smkList.obj"
	-@erase "$(INTDIR)\smkParse.obj"
	-@erase "$(INTDIR)\smkPaSema.obj"
	-@erase "$(INTDIR)\smkScan.obj"
	-@erase "$(INTDIR)\smkScSema.obj"
	-@erase "$(INTDIR)\time.obj"
	-@erase "$(INTDIR)\token.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(INTDIR)\vocabulary.obj"
	-@erase "$(INTDIR)\write.obj"
	-@erase ".\smk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\tmk" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\tmk" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AMOSDEV" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\license" /I "..\tmk" /I "..\imp" /D\
 "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AMOSDEV" /Fp"$(INTDIR)/smk.pch" /YX\
 /Fo"$(INTDIR)/" /c
CPP_OBJS=.\smk___Wi/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/smk.bsc"
BSC32_SBRS= \

LINK32=link.exe
# ADD BASE LINK32 ..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"smk.exe"
LINK32_FLAGS=..\license\license.lib ..\tmk\tmklib.lib ..\imp\implib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/smk.pdb" /machine:I386\
 /out:"smk.exe"
LINK32_OBJS= \
	"$(INTDIR)\action.obj" \
	"$(INTDIR)\ast.obj" \
	"$(INTDIR)\char.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\definition.obj" \
	"$(INTDIR)\dfa.obj" \
	"$(INTDIR)\lmprintf.obj" \
	"$(INTDIR)\lookahead.obj" \
	"$(INTDIR)\map.obj" \
	"$(INTDIR)\name.obj" \
	"$(INTDIR)\nfa.obj" \
	"$(INTDIR)\nfas.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\rule.obj" \
	"$(INTDIR)\scanner.obj" \
	"$(INTDIR)\screen.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\smalloc.obj" \
	"$(INTDIR)\smk.obj" \
	"$(INTDIR)\smkErr.obj" \
	"$(INTDIR)\smkList.obj" \
	"$(INTDIR)\smkParse.obj" \
	"$(INTDIR)\smkPaSema.obj" \
	"$(INTDIR)\smkScan.obj" \
	"$(INTDIR)\smkScSema.obj" \
	"$(INTDIR)\time.obj" \
	"$(INTDIR)\token.obj" \
	"$(INTDIR)\version.obj" \
	"$(INTDIR)\vocabulary.obj" \
	"$(INTDIR)\write.obj"

".\smk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<

################################################################################
# Begin Target

# Name "smk - Win32 Release"
# Name "smk - Win32 Debug"
# Name "smk - Win32 Test"
# Name "smk - Win32 AMOS"

!IF  "$(CFG)" == "smk - Win32 Release"

!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

!ELSEIF  "$(CFG)" == "smk - Win32 Test"

!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

!ENDIF

################################################################################
# Begin Source File

SOURCE=.\version.c
DEP_CPP_VERSI=\
	".\version.h"\


!IF  "$(CFG)" == "smk - Win32 Release"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ast.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_AST_C=\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\lmprintf.h"\
	".\name.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\ast.obj" : $(SOURCE) $(DEP_CPP_AST_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_AST_C=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\ast.obj" : $(SOURCE) $(DEP_CPP_AST_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_AST_C=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\ast.obj" : $(SOURCE) $(DEP_CPP_AST_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_AST_C=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\ast.obj" : $(SOURCE) $(DEP_CPP_AST_C) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\char.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_CHAR_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\char.obj" : $(SOURCE) $(DEP_CPP_CHAR_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_CHAR_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\char.obj" : $(SOURCE) $(DEP_CPP_CHAR_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_CHAR_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\char.obj" : $(SOURCE) $(DEP_CPP_CHAR_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_CHAR_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\char.obj" : $(SOURCE) $(DEP_CPP_CHAR_) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\common.c
DEP_CPP_COMMO=\
	".\common.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


!IF  "$(CFG)" == "smk - Win32 Release"


"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"


"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"


"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"


"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\definition.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_DEFIN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\definition.obj" : $(SOURCE) $(DEP_CPP_DEFIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_DEFIN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\definition.obj" : $(SOURCE) $(DEP_CPP_DEFIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_DEFIN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\definition.obj" : $(SOURCE) $(DEP_CPP_DEFIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_DEFIN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\definition.obj" : $(SOURCE) $(DEP_CPP_DEFIN) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dfa.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_DFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\dfa.obj" : $(SOURCE) $(DEP_CPP_DFA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_DFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\dfa.obj" : $(SOURCE) $(DEP_CPP_DFA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_DFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\dfa.obj" : $(SOURCE) $(DEP_CPP_DFA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_DFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\dfa.obj" : $(SOURCE) $(DEP_CPP_DFA_C) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmprintf.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_LMPRI=\
	".\common.h"\
	".\lmprintf.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lmprintf.obj" : $(SOURCE) $(DEP_CPP_LMPRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_LMPRI=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lmprintf.obj" : $(SOURCE) $(DEP_CPP_LMPRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_LMPRI=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lmprintf.obj" : $(SOURCE) $(DEP_CPP_LMPRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_LMPRI=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lmprintf.obj" : $(SOURCE) $(DEP_CPP_LMPRI) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lookahead.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_LOOKA=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lookahead.obj" : $(SOURCE) $(DEP_CPP_LOOKA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_LOOKA=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lookahead.obj" : $(SOURCE) $(DEP_CPP_LOOKA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_LOOKA=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lookahead.obj" : $(SOURCE) $(DEP_CPP_LOOKA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_LOOKA=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\lookahead.obj" : $(SOURCE) $(DEP_CPP_LOOKA) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\map.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_MAP_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\char.h"\
	".\lmprintf.h"\
	".\map.h"\
	".\name.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\


"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_MAP_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_MAP_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_MAP_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\name.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_NAME_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmprintf.h"\
	".\name.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\


"$(INTDIR)\name.obj" : $(SOURCE) $(DEP_CPP_NAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_NAME_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\name.obj" : $(SOURCE) $(DEP_CPP_NAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_NAME_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\name.obj" : $(SOURCE) $(DEP_CPP_NAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_NAME_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\name.obj" : $(SOURCE) $(DEP_CPP_NAME_) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\nfa.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_NFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfa.obj" : $(SOURCE) $(DEP_CPP_NFA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_NFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfa.obj" : $(SOURCE) $(DEP_CPP_NFA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_NFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfa.obj" : $(SOURCE) $(DEP_CPP_NFA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_NFA_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfa.obj" : $(SOURCE) $(DEP_CPP_NFA_C) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\nfas.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_NFAS_=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfas.obj" : $(SOURCE) $(DEP_CPP_NFAS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_NFAS_=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfas.obj" : $(SOURCE) $(DEP_CPP_NFAS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_NFAS_=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfas.obj" : $(SOURCE) $(DEP_CPP_NFAS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_NFAS_=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\nfas.obj" : $(SOURCE) $(DEP_CPP_NFAS_) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pack.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_PACK_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\name.h"\
	".\pack.h"\
	".\smk_i.h"\


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_PACK_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\name.h"\
	".\pack.h"\
	".\smk_i.h"\


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_PACK_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\name.h"\
	".\pack.h"\
	".\smk_i.h"\


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_PACK_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\name.h"\
	".\pack.h"\
	".\smk_i.h"\


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rule.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_RULE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\rule.obj" : $(SOURCE) $(DEP_CPP_RULE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_RULE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\rule.obj" : $(SOURCE) $(DEP_CPP_RULE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_RULE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\rule.obj" : $(SOURCE) $(DEP_CPP_RULE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_RULE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\rule.obj" : $(SOURCE) $(DEP_CPP_RULE_) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scanner.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SCANN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\scanner.obj" : $(SOURCE) $(DEP_CPP_SCANN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SCANN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\scanner.obj" : $(SOURCE) $(DEP_CPP_SCANN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SCANN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\scanner.obj" : $(SOURCE) $(DEP_CPP_SCANN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SCANN=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\scanner.obj" : $(SOURCE) $(DEP_CPP_SCANN) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\screen.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SCREE=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\screen.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SCREE=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\screen.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SCREE=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\screen.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SCREE=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\screen.obj" : $(SOURCE) $(DEP_CPP_SCREE) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\set.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SET_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\char.h"\
	".\lmprintf.h"\
	".\name.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SET_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SET_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SET_C=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smalloc.c
DEP_CPP_SMALL=\
	".\common.h"\
	".\smalloc.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


!IF  "$(CFG)" == "smk - Win32 Release"


"$(INTDIR)\smalloc.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"


"$(INTDIR)\smalloc.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"


"$(INTDIR)\smalloc.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"


"$(INTDIR)\smalloc.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smk.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\time.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	".\write.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smk.obj" : $(SOURCE) $(DEP_CPP_SMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\time.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	".\write.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smk.obj" : $(SOURCE) $(DEP_CPP_SMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\time.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	".\write.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smk.obj" : $(SOURCE) $(DEP_CPP_SMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\char.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\time.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	".\write.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smk.obj" : $(SOURCE) $(DEP_CPP_SMK_C) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smkErr.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkErr.obj" : $(SOURCE) $(DEP_CPP_SMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkErr.obj" : $(SOURCE) $(DEP_CPP_SMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkErr.obj" : $(SOURCE) $(DEP_CPP_SMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkErr.obj" : $(SOURCE) $(DEP_CPP_SMKER) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smkList.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMKLI=\
	".\smkCommon.h"\
	".\smkList.h"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkList.obj" : $(SOURCE) $(DEP_CPP_SMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMKLI=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkList.obj" : $(SOURCE) $(DEP_CPP_SMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMKLI=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkList.obj" : $(SOURCE) $(DEP_CPP_SMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMKLI=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkList.obj" : $(SOURCE) $(DEP_CPP_SMKLI) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smkParse.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkParse.obj" : $(SOURCE) $(DEP_CPP_SMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkParse.obj" : $(SOURCE) $(DEP_CPP_SMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkParse.obj" : $(SOURCE) $(DEP_CPP_SMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkParse.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkParse.obj" : $(SOURCE) $(DEP_CPP_SMKPA) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smkPaSema.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkPaSema.obj" : $(SOURCE) $(DEP_CPP_SMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkPaSema.obj" : $(SOURCE) $(DEP_CPP_SMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkPaSema.obj" : $(SOURCE) $(DEP_CPP_SMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\definition.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkPaSema.obj" : $(SOURCE) $(DEP_CPP_SMKPAS) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smkScan.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScan.obj" : $(SOURCE) $(DEP_CPP_SMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScan.obj" : $(SOURCE) $(DEP_CPP_SMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScan.obj" : $(SOURCE) $(DEP_CPP_SMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScan.obj" : $(SOURCE) $(DEP_CPP_SMKSC) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\smkScSema.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_SMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScSema.obj" : $(SOURCE) $(DEP_CPP_SMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_SMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScSema.obj" : $(SOURCE) $(DEP_CPP_SMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_SMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScSema.obj" : $(SOURCE) $(DEP_CPP_SMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_SMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\smkScSema.obj" : $(SOURCE) $(DEP_CPP_SMKSCS) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\time.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_TIME_=\
	".\time.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\time.obj" : $(SOURCE) $(DEP_CPP_TIME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_TIME_=\
	".\time.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\time.obj" : $(SOURCE) $(DEP_CPP_TIME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_TIME_=\
	".\time.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\time.obj" : $(SOURCE) $(DEP_CPP_TIME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_TIME_=\
	".\time.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\time.obj" : $(SOURCE) $(DEP_CPP_TIME_) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\token.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_TOKEN=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\token.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_TOKEN=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\token.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_TOKEN=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\token.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_TOKEN=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\token.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\action.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_ACTIO=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\action.obj" : $(SOURCE) $(DEP_CPP_ACTIO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_ACTIO=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\action.obj" : $(SOURCE) $(DEP_CPP_ACTIO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_ACTIO=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\action.obj" : $(SOURCE) $(DEP_CPP_ACTIO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_ACTIO=\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\action.obj" : $(SOURCE) $(DEP_CPP_ACTIO) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vocabulary.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_VOCAB=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\vocabulary.obj" : $(SOURCE) $(DEP_CPP_VOCAB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_VOCAB=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\vocabulary.obj" : $(SOURCE) $(DEP_CPP_VOCAB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_VOCAB=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\vocabulary.obj" : $(SOURCE) $(DEP_CPP_VOCAB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_VOCAB=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkList.h"\
	".\smkScan.h"\
	".\token.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\vocabulary.obj" : $(SOURCE) $(DEP_CPP_VOCAB) "$(INTDIR)"


!ENDIF

# End Source File
################################################################################
# Begin Source File

SOURCE=.\write.c

!IF  "$(CFG)" == "smk - Win32 Release"

DEP_CPP_WRITE=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\write.obj" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Debug"

DEP_CPP_WRITE=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\write.obj" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 Test"

DEP_CPP_WRITE=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\write.obj" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "smk - Win32 AMOS"

DEP_CPP_WRITE=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\action.h"\
	".\ast.h"\
	".\common.h"\
	".\dfa.h"\
	".\lmprintf.h"\
	".\lookahead.h"\
	".\map.h"\
	".\name.h"\
	".\nfa.h"\
	".\nfas.h"\
	".\pack.h"\
	".\rule.h"\
	".\scanner.h"\
	".\screen.h"\
	".\set.h"\
	".\smalloc.h"\
	".\smk_i.h"\
	".\smkCommon.h"\
	".\smkScan.h"\
	".\token.h"\
	".\version.h"\
	".\vocabulary.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TIME.H"\


"$(INTDIR)\write.obj" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


!ENDIF

# End Source File
# End Target
# End Project
################################################################################
