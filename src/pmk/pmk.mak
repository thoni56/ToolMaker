# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=pmk - Win32 Test
!MESSAGE No configuration specified.  Defaulting to pmk - Win32 Test.
!ENDIF 

!IF "$(CFG)" != "pmk - Win32 Release" && "$(CFG)" != "pmk - Win32 Debug" &&\
 "$(CFG)" != "pmk - Win32 Test" && "$(CFG)" != "pmk - Win32 AMOS"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "pmk.mak" CFG="pmk - Win32 Test"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pmk - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pmk - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "pmk - Win32 Test" (based on "Win32 (x86) Console Application")
!MESSAGE "pmk - Win32 AMOS" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "pmk - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pmk - Win32 Release"

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

ALL : "$(OUTDIR)\pmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\pmk.obj"
	-@erase "$(INTDIR)\pmkErr.obj"
	-@erase "$(INTDIR)\pmkList.obj"
	-@erase "$(INTDIR)\pmkParse.obj"
	-@erase "$(INTDIR)\pmkPaSema.obj"
	-@erase "$(INTDIR)\pmkScan.obj"
	-@erase "$(INTDIR)\pmkScSema.obj"
	-@erase "$(INTDIR)\pmkSymTab.obj"
	-@erase "$(INTDIR)\pmkTab.obj"
	-@erase "$(INTDIR)\pwDbg.obj"
	-@erase "$(INTDIR)\pwGe.obj"
	-@erase "$(INTDIR)\pwLog.obj"
	-@erase "$(INTDIR)\pwPack.obj"
	-@erase "$(INTDIR)\pwsGrm.obj"
	-@erase "$(INTDIR)\pwsOrd.obj"
	-@erase "$(INTDIR)\pwsQueue.obj"
	-@erase "$(INTDIR)\pwsWrit.obj"
	-@erase "$(INTDIR)\pwSymSet.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\timing.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\pmk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\imp" /I "..\tmk" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\license" /I "..\imp" /I "..\tmk" /D\
 "NDEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/pmk.pch" /YX /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/pmk.pdb" /machine:I386\
 /out:"$(OUTDIR)/pmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\pmk.obj" \
	"$(INTDIR)\pmkErr.obj" \
	"$(INTDIR)\pmkList.obj" \
	"$(INTDIR)\pmkParse.obj" \
	"$(INTDIR)\pmkPaSema.obj" \
	"$(INTDIR)\pmkScan.obj" \
	"$(INTDIR)\pmkScSema.obj" \
	"$(INTDIR)\pmkSymTab.obj" \
	"$(INTDIR)\pmkTab.obj" \
	"$(INTDIR)\pwDbg.obj" \
	"$(INTDIR)\pwGe.obj" \
	"$(INTDIR)\pwLog.obj" \
	"$(INTDIR)\pwPack.obj" \
	"$(INTDIR)\pwsGrm.obj" \
	"$(INTDIR)\pwsOrd.obj" \
	"$(INTDIR)\pwsQueue.obj" \
	"$(INTDIR)\pwsWrit.obj" \
	"$(INTDIR)\pwSymSet.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\timing.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\pmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

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

ALL : "$(OUTDIR)\pmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\pmk.obj"
	-@erase "$(INTDIR)\pmkErr.obj"
	-@erase "$(INTDIR)\pmkList.obj"
	-@erase "$(INTDIR)\pmkParse.obj"
	-@erase "$(INTDIR)\pmkPaSema.obj"
	-@erase "$(INTDIR)\pmkScan.obj"
	-@erase "$(INTDIR)\pmkScSema.obj"
	-@erase "$(INTDIR)\pmkSymTab.obj"
	-@erase "$(INTDIR)\pmkTab.obj"
	-@erase "$(INTDIR)\pwDbg.obj"
	-@erase "$(INTDIR)\pwGe.obj"
	-@erase "$(INTDIR)\pwLog.obj"
	-@erase "$(INTDIR)\pwPack.obj"
	-@erase "$(INTDIR)\pwsGrm.obj"
	-@erase "$(INTDIR)\pwsOrd.obj"
	-@erase "$(INTDIR)\pwsQueue.obj"
	-@erase "$(INTDIR)\pwsWrit.obj"
	-@erase "$(INTDIR)\pwSymSet.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\timing.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\pmk.exe"
	-@erase "$(OUTDIR)\pmk.ilk"
	-@erase "$(OUTDIR)\pmk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /I "..\tmk" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /I\
 "..\tmk" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/pmk.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/pmk.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/pmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\pmk.obj" \
	"$(INTDIR)\pmkErr.obj" \
	"$(INTDIR)\pmkList.obj" \
	"$(INTDIR)\pmkParse.obj" \
	"$(INTDIR)\pmkPaSema.obj" \
	"$(INTDIR)\pmkScan.obj" \
	"$(INTDIR)\pmkScSema.obj" \
	"$(INTDIR)\pmkSymTab.obj" \
	"$(INTDIR)\pmkTab.obj" \
	"$(INTDIR)\pwDbg.obj" \
	"$(INTDIR)\pwGe.obj" \
	"$(INTDIR)\pwLog.obj" \
	"$(INTDIR)\pwPack.obj" \
	"$(INTDIR)\pwsGrm.obj" \
	"$(INTDIR)\pwsOrd.obj" \
	"$(INTDIR)\pwsQueue.obj" \
	"$(INTDIR)\pwsWrit.obj" \
	"$(INTDIR)\pwSymSet.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\timing.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\pmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "pmk___Wi"
# PROP BASE Intermediate_Dir "pmk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\pmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\pmk.obj"
	-@erase "$(INTDIR)\pmkErr.obj"
	-@erase "$(INTDIR)\pmkList.obj"
	-@erase "$(INTDIR)\pmkParse.obj"
	-@erase "$(INTDIR)\pmkPaSema.obj"
	-@erase "$(INTDIR)\pmkScan.obj"
	-@erase "$(INTDIR)\pmkScSema.obj"
	-@erase "$(INTDIR)\pmkSymTab.obj"
	-@erase "$(INTDIR)\pmkTab.obj"
	-@erase "$(INTDIR)\pwDbg.obj"
	-@erase "$(INTDIR)\pwGe.obj"
	-@erase "$(INTDIR)\pwLog.obj"
	-@erase "$(INTDIR)\pwPack.obj"
	-@erase "$(INTDIR)\pwsGrm.obj"
	-@erase "$(INTDIR)\pwsOrd.obj"
	-@erase "$(INTDIR)\pwsQueue.obj"
	-@erase "$(INTDIR)\pwsWrit.obj"
	-@erase "$(INTDIR)\pwSymSet.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\timing.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\pmk.exe"
	-@erase "$(OUTDIR)\pmk.ilk"
	-@erase "$(OUTDIR)\pmk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /I "..\tmk" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /I "..\tmk" /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\license" /I "..\imp" /I\
 "..\tmk" /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/pmk.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/pmk.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/pmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\pmk.obj" \
	"$(INTDIR)\pmkErr.obj" \
	"$(INTDIR)\pmkList.obj" \
	"$(INTDIR)\pmkParse.obj" \
	"$(INTDIR)\pmkPaSema.obj" \
	"$(INTDIR)\pmkScan.obj" \
	"$(INTDIR)\pmkScSema.obj" \
	"$(INTDIR)\pmkSymTab.obj" \
	"$(INTDIR)\pmkTab.obj" \
	"$(INTDIR)\pwDbg.obj" \
	"$(INTDIR)\pwGe.obj" \
	"$(INTDIR)\pwLog.obj" \
	"$(INTDIR)\pwPack.obj" \
	"$(INTDIR)\pwsGrm.obj" \
	"$(INTDIR)\pwsOrd.obj" \
	"$(INTDIR)\pwsQueue.obj" \
	"$(INTDIR)\pwsWrit.obj" \
	"$(INTDIR)\pwSymSet.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\timing.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\pmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pmk___Wi"
# PROP BASE Intermediate_Dir "pmk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "pmk___Wi"
# PROP Intermediate_Dir "pmk___Wi"
# PROP Target_Dir ""
OUTDIR=.\pmk___Wi
INTDIR=.\pmk___Wi

ALL : ".\pmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\pmk.obj"
	-@erase "$(INTDIR)\pmkErr.obj"
	-@erase "$(INTDIR)\pmkList.obj"
	-@erase "$(INTDIR)\pmkParse.obj"
	-@erase "$(INTDIR)\pmkPaSema.obj"
	-@erase "$(INTDIR)\pmkScan.obj"
	-@erase "$(INTDIR)\pmkScSema.obj"
	-@erase "$(INTDIR)\pmkSymTab.obj"
	-@erase "$(INTDIR)\pmkTab.obj"
	-@erase "$(INTDIR)\pwDbg.obj"
	-@erase "$(INTDIR)\pwGe.obj"
	-@erase "$(INTDIR)\pwLog.obj"
	-@erase "$(INTDIR)\pwPack.obj"
	-@erase "$(INTDIR)\pwsGrm.obj"
	-@erase "$(INTDIR)\pwsOrd.obj"
	-@erase "$(INTDIR)\pwsQueue.obj"
	-@erase "$(INTDIR)\pwsWrit.obj"
	-@erase "$(INTDIR)\pwSymSet.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\timing.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase ".\pmk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\imp" /I "..\tmk" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\license" /I "..\imp" /I "..\tmk" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AMOSDEV" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\license" /I "..\imp" /I "..\tmk" /D\
 "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AMOSDEV" /Fp"$(INTDIR)/pmk.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\pmk___Wi/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"pmk.exe"
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/pmk.pdb" /machine:I386\
 /out:"pmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\pmk.obj" \
	"$(INTDIR)\pmkErr.obj" \
	"$(INTDIR)\pmkList.obj" \
	"$(INTDIR)\pmkParse.obj" \
	"$(INTDIR)\pmkPaSema.obj" \
	"$(INTDIR)\pmkScan.obj" \
	"$(INTDIR)\pmkScSema.obj" \
	"$(INTDIR)\pmkSymTab.obj" \
	"$(INTDIR)\pmkTab.obj" \
	"$(INTDIR)\pwDbg.obj" \
	"$(INTDIR)\pwGe.obj" \
	"$(INTDIR)\pwLog.obj" \
	"$(INTDIR)\pwPack.obj" \
	"$(INTDIR)\pwsGrm.obj" \
	"$(INTDIR)\pwsOrd.obj" \
	"$(INTDIR)\pwsQueue.obj" \
	"$(INTDIR)\pwsWrit.obj" \
	"$(INTDIR)\pwSymSet.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\timing.obj" \
	"$(INTDIR)\version.obj"

".\pmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "pmk - Win32 Release"
# Name "pmk - Win32 Debug"
# Name "pmk - Win32 Test"
# Name "pmk - Win32 AMOS"

!IF  "$(CFG)" == "pmk - Win32 Release"

!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\pmk.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\timing.h"\
	".\version.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\pmk.obj" : $(SOURCE) $(DEP_CPP_PMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\timing.h"\
	".\version.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\pmk.obj" : $(SOURCE) $(DEP_CPP_PMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\timing.h"\
	".\version.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\pmk.obj" : $(SOURCE) $(DEP_CPP_PMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\timing.h"\
	".\version.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\pmk.obj" : $(SOURCE) $(DEP_CPP_PMK_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pack.c
DEP_CPP_PACK_=\
	".\pack.h"\
	

!IF  "$(CFG)" == "pmk - Win32 Release"


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"


"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkErr.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkErr.obj" : $(SOURCE) $(DEP_CPP_PMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkErr.obj" : $(SOURCE) $(DEP_CPP_PMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkErr.obj" : $(SOURCE) $(DEP_CPP_PMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkErr.obj" : $(SOURCE) $(DEP_CPP_PMKER) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkList.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKLI=\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	

"$(INTDIR)\pmkList.obj" : $(SOURCE) $(DEP_CPP_PMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKLI=\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	

"$(INTDIR)\pmkList.obj" : $(SOURCE) $(DEP_CPP_PMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKLI=\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	

"$(INTDIR)\pmkList.obj" : $(SOURCE) $(DEP_CPP_PMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKLI=\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	

"$(INTDIR)\pmkList.obj" : $(SOURCE) $(DEP_CPP_PMKLI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkParse.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkParse.obj" : $(SOURCE) $(DEP_CPP_PMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkParse.obj" : $(SOURCE) $(DEP_CPP_PMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkParse.obj" : $(SOURCE) $(DEP_CPP_PMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkParse.obj" : $(SOURCE) $(DEP_CPP_PMKPA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkPaSema.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkPaSema.obj" : $(SOURCE) $(DEP_CPP_PMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkPaSema.obj" : $(SOURCE) $(DEP_CPP_PMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkPaSema.obj" : $(SOURCE) $(DEP_CPP_PMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkPaSema.obj" : $(SOURCE) $(DEP_CPP_PMKPAS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkScan.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScan.obj" : $(SOURCE) $(DEP_CPP_PMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScan.obj" : $(SOURCE) $(DEP_CPP_PMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScan.obj" : $(SOURCE) $(DEP_CPP_PMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScan.obj" : $(SOURCE) $(DEP_CPP_PMKSC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkScSema.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScSema.obj" : $(SOURCE) $(DEP_CPP_PMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScSema.obj" : $(SOURCE) $(DEP_CPP_PMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScSema.obj" : $(SOURCE) $(DEP_CPP_PMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkScan.h"\
	".\pws.h"\
	".\pwsLexCode.h"\
	

"$(INTDIR)\pmkScSema.obj" : $(SOURCE) $(DEP_CPP_PMKSCS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkSymTab.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKSY=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkSymTab.obj" : $(SOURCE) $(DEP_CPP_PMKSY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKSY=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkSymTab.obj" : $(SOURCE) $(DEP_CPP_PMKSY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKSY=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkSymTab.obj" : $(SOURCE) $(DEP_CPP_PMKSY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKSY=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pmkSymTab.obj" : $(SOURCE) $(DEP_CPP_PMKSY) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmkTab.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PMKTA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\version.h"\
	

"$(INTDIR)\pmkTab.obj" : $(SOURCE) $(DEP_CPP_PMKTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PMKTA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\version.h"\
	

"$(INTDIR)\pmkTab.obj" : $(SOURCE) $(DEP_CPP_PMKTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PMKTA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\version.h"\
	

"$(INTDIR)\pmkTab.obj" : $(SOURCE) $(DEP_CPP_PMKTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PMKTA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkParse.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwSymSet.h"\
	".\set.h"\
	".\version.h"\
	

"$(INTDIR)\pmkTab.obj" : $(SOURCE) $(DEP_CPP_PMKTA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwDbg.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWDBG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwDbg.obj" : $(SOURCE) $(DEP_CPP_PWDBG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWDBG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwDbg.obj" : $(SOURCE) $(DEP_CPP_PWDBG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWDBG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwDbg.obj" : $(SOURCE) $(DEP_CPP_PWDBG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWDBG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwDbg.obj" : $(SOURCE) $(DEP_CPP_PWDBG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwGe.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWGE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwGe.obj" : $(SOURCE) $(DEP_CPP_PWGE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWGE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwGe.obj" : $(SOURCE) $(DEP_CPP_PWGE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWGE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwGe.obj" : $(SOURCE) $(DEP_CPP_PWGE_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWGE_=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwDbg.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwGe.obj" : $(SOURCE) $(DEP_CPP_PWGE_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwLog.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWLOG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwLog.obj" : $(SOURCE) $(DEP_CPP_PWLOG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWLOG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwLog.obj" : $(SOURCE) $(DEP_CPP_PWLOG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWLOG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwLog.obj" : $(SOURCE) $(DEP_CPP_PWLOG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWLOG=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwLog.obj" : $(SOURCE) $(DEP_CPP_PWLOG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwPack.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWPAC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwPack.obj" : $(SOURCE) $(DEP_CPP_PWPAC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWPAC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwPack.obj" : $(SOURCE) $(DEP_CPP_PWPAC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWPAC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwPack.obj" : $(SOURCE) $(DEP_CPP_PWPAC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWPAC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pack.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pwLog.h"\
	".\pwPack.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwPack.obj" : $(SOURCE) $(DEP_CPP_PWPAC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwsGrm.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWSGR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwsQueue.h"\
	".\pwsWrit.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsGrm.obj" : $(SOURCE) $(DEP_CPP_PWSGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWSGR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwsQueue.h"\
	".\pwsWrit.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsGrm.obj" : $(SOURCE) $(DEP_CPP_PWSGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWSGR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwsQueue.h"\
	".\pwsWrit.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsGrm.obj" : $(SOURCE) $(DEP_CPP_PWSGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWSGR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsLexCode.h"\
	".\pwsOrd.h"\
	".\pwsQueue.h"\
	".\pwsWrit.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsGrm.obj" : $(SOURCE) $(DEP_CPP_PWSGR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwsOrd.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWSOR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsOrd.obj" : $(SOURCE) $(DEP_CPP_PWSOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWSOR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsOrd.obj" : $(SOURCE) $(DEP_CPP_PWSOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWSOR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsOrd.obj" : $(SOURCE) $(DEP_CPP_PWSOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWSOR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmk_i.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsOrd.obj" : $(SOURCE) $(DEP_CPP_PWSOR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwsQueue.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWSQU=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsQueue.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsQueue.obj" : $(SOURCE) $(DEP_CPP_PWSQU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWSQU=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsQueue.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsQueue.obj" : $(SOURCE) $(DEP_CPP_PWSQU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWSQU=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsQueue.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsQueue.obj" : $(SOURCE) $(DEP_CPP_PWSQU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWSQU=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsQueue.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsQueue.obj" : $(SOURCE) $(DEP_CPP_PWSQU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwsWrit.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWSWR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsWrit.obj" : $(SOURCE) $(DEP_CPP_PWSWR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWSWR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsWrit.obj" : $(SOURCE) $(DEP_CPP_PWSWR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWSWR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsWrit.obj" : $(SOURCE) $(DEP_CPP_PWSWR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWSWR=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pwGe.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwsOrd.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwsWrit.obj" : $(SOURCE) $(DEP_CPP_PWSWR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pwSymSet.c

!IF  "$(CFG)" == "pmk - Win32 Release"

DEP_CPP_PWSYM=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwSymSet.obj" : $(SOURCE) $(DEP_CPP_PWSYM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"

DEP_CPP_PWSYM=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwSymSet.obj" : $(SOURCE) $(DEP_CPP_PWSYM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"

DEP_CPP_PWSYM=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwSymSet.obj" : $(SOURCE) $(DEP_CPP_PWSYM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"

DEP_CPP_PWSYM=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\pmkCommon.h"\
	".\pmkList.h"\
	".\pmkSymTab.h"\
	".\pws.h"\
	".\pwsGrm.h"\
	".\pwSymSet.h"\
	".\set.h"\
	

"$(INTDIR)\pwSymSet.obj" : $(SOURCE) $(DEP_CPP_PWSYM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\set.c
DEP_CPP_SET_C=\
	".\set.h"\
	

!IF  "$(CFG)" == "pmk - Win32 Release"


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"


"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timing.c
DEP_CPP_TIMIN=\
	".\timing.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

!IF  "$(CFG)" == "pmk - Win32 Release"


"$(INTDIR)\timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"


"$(INTDIR)\timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"


"$(INTDIR)\timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"


"$(INTDIR)\timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\version.c
DEP_CPP_VERSI=\
	".\version.h"\
	

!IF  "$(CFG)" == "pmk - Win32 Release"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Debug"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 Test"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmk - Win32 AMOS"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
