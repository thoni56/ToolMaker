# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=toolmake - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to toolmake - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "toolmake - Win32 Release" && "$(CFG)" !=\
 "toolmake - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "toolmake.mak" CFG="toolmake - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "toolmake - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "toolmake - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "toolmake - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "toolmake - Win32 Release"

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

ALL : "$(OUTDIR)\toolmake.exe"

CLEAN : 
	-@erase "$(INTDIR)\ask.obj"
	-@erase "$(INTDIR)\menue.obj"
	-@erase "$(INTDIR)\spa.obj"
	-@erase "$(INTDIR)\system.obj"
	-@erase "$(INTDIR)\toolmake.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\toolmake.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /D TMHOME="""C:\\Program\\ToolMaker""" /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\license" /I "..\imp" /D "NDEBUG" /D\
 "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/toolmake.pch" /YX /Fo"$(INTDIR)/" /D\
 TMHOME="""C:\\Program\\ToolMaker""" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/toolmake.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/toolmake.pdb" /machine:I386\
 /out:"$(OUTDIR)/toolmake.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ask.obj" \
	"$(INTDIR)\menue.obj" \
	"$(INTDIR)\spa.obj" \
	"$(INTDIR)\system.obj" \
	"$(INTDIR)\toolmake.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\toolmake.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "toolmake - Win32 Debug"

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

ALL : "$(OUTDIR)\toolmake.exe"

CLEAN : 
	-@erase "$(INTDIR)\ask.obj"
	-@erase "$(INTDIR)\menue.obj"
	-@erase "$(INTDIR)\spa.obj"
	-@erase "$(INTDIR)\system.obj"
	-@erase "$(INTDIR)\toolmake.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\toolmake.exe"
	-@erase "$(OUTDIR)\toolmake.ilk"
	-@erase "$(OUTDIR)\toolmake.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /D TMHOME="""C:\\Program\\ToolMaker""" /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /D\
 "_DEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/toolmake.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /D TMHOME="""C:\\Program\\ToolMaker""" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/toolmake.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/toolmake.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/toolmake.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ask.obj" \
	"$(INTDIR)\menue.obj" \
	"$(INTDIR)\spa.obj" \
	"$(INTDIR)\system.obj" \
	"$(INTDIR)\toolmake.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\toolmake.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "toolmake - Win32 Release"
# Name "toolmake - Win32 Debug"

!IF  "$(CFG)" == "toolmake - Win32 Release"

!ELSEIF  "$(CFG)" == "toolmake - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\version.c
DEP_CPP_VERSI=\
	".\version.h"\
	

"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\menue.c
DEP_CPP_MENUE=\
	".\ask.h"\
	

"$(INTDIR)\menue.obj" : $(SOURCE) $(DEP_CPP_MENUE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\spa.c
DEP_CPP_SPA_C=\
	".\spa.h"\
	

"$(INTDIR)\spa.obj" : $(SOURCE) $(DEP_CPP_SPA_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\system.c
DEP_CPP_SYSTE=\
	".\system.h"\
	".\toolmake.h"\
	{$(INCLUDE)}"\sys\stat.h"\
	{$(INCLUDE)}"\sys\types.h"\
	

"$(INTDIR)\system.obj" : $(SOURCE) $(DEP_CPP_SYSTE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\toolmake.c
DEP_CPP_TOOLM=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	".\ask.h"\
	".\spa.h"\
	".\system.h"\
	".\toolmake.h"\
	".\version.h"\
	

"$(INTDIR)\toolmake.obj" : $(SOURCE) $(DEP_CPP_TOOLM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ask.c
DEP_CPP_ASK_C=\
	".\ask.h"\
	

"$(INTDIR)\ask.obj" : $(SOURCE) $(DEP_CPP_ASK_C) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
