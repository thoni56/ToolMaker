# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=imp - Win32 Test
!MESSAGE No configuration specified.  Defaulting to imp - Win32 Test.
!ENDIF 

!IF "$(CFG)" != "imp - Win32 Release" && "$(CFG)" != "imp - Win32 Debug" &&\
 "$(CFG)" != "imp - Win32 Test"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "imp.mak" CFG="imp - Win32 Test"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "imp - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "imp - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "imp - Win32 Test" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "imp - Win32 Test"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "imp - Win32 Release"

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

ALL : "$(OUTDIR)\imp.exe"

CLEAN : 
	-@erase "$(INTDIR)\imp.obj"
	-@erase "$(OUTDIR)\imp.exe"
	-@erase "$(OUTDIR)\imp.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/imp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/imp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /machine:I386
LINK32_FLAGS=..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/imp.pdb" /machine:I386 /out:"$(OUTDIR)/imp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\imp.obj"

"$(OUTDIR)\imp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "imp - Win32 Debug"

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

ALL : "$(OUTDIR)\imp.exe"

CLEAN : 
	-@erase "$(INTDIR)\imp.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\imp.exe"
	-@erase "$(OUTDIR)\imp.ilk"
	-@erase "$(OUTDIR)\imp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/imp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/imp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/imp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/imp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\imp.obj"

"$(OUTDIR)\imp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "imp - Win32 Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "imp___Wi"
# PROP BASE Intermediate_Dir "imp___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\imp.exe"

CLEAN : 
	-@erase "$(INTDIR)\imp.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\imp.exe"
	-@erase "$(OUTDIR)\imp.ilk"
	-@erase "$(OUTDIR)\imp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "TMTEST" /D "WIN32" /D\
 "_CONSOLE" /Fp"$(INTDIR)/imp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/imp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=..\imp\implib.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/imp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/imp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\imp.obj"

"$(OUTDIR)\imp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "imp - Win32 Release"
# Name "imp - Win32 Debug"
# Name "imp - Win32 Test"

!IF  "$(CFG)" == "imp - Win32 Release"

!ELSEIF  "$(CFG)" == "imp - Win32 Debug"

!ELSEIF  "$(CFG)" == "imp - Win32 Test"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\imp.c

!IF  "$(CFG)" == "imp - Win32 Release"

DEP_CPP_IMP_C=\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\version.h"\
	

"$(INTDIR)\imp.obj" : $(SOURCE) $(DEP_CPP_IMP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "imp - Win32 Debug"

DEP_CPP_IMP_C=\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\version.h"\
	

"$(INTDIR)\imp.obj" : $(SOURCE) $(DEP_CPP_IMP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "imp - Win32 Test"

DEP_CPP_IMP_C=\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\version.h"\
	

"$(INTDIR)\imp.obj" : $(SOURCE) $(DEP_CPP_IMP_C) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
