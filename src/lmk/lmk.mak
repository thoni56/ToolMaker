# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=lmk - Win32 Test
!MESSAGE No configuration specified.  Defaulting to lmk - Win32 Test.
!ENDIF 

!IF "$(CFG)" != "lmk - Win32 Release" && "$(CFG)" != "lmk - Win32 Debug" &&\
 "$(CFG)" != "lmk - Win32 Test" && "$(CFG)" != "lmk - Win32 AMOS"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "lmk.mak" CFG="lmk - Win32 Test"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lmk - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "lmk - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "lmk - Win32 Test" (based on "Win32 (x86) Console Application")
!MESSAGE "lmk - Win32 AMOS" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "lmk - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "lmk - Win32 Release"

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

ALL : "$(OUTDIR)\lmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\lmk.obj"
	-@erase "$(INTDIR)\lmkErr.obj"
	-@erase "$(INTDIR)\lmkList.obj"
	-@erase "$(INTDIR)\lmkParse.obj"
	-@erase "$(INTDIR)\lmkPaSema.obj"
	-@erase "$(INTDIR)\lmkScan.obj"
	-@erase "$(INTDIR)\lmkScSema.obj"
	-@erase "$(INTDIR)\lmkTab.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\lmk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\tmk" /I "..\license" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\tmk" /I "..\license" /I "..\imp" /D\
 "NDEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/lmk.pch" /YX /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/lmk.pdb" /machine:I386\
 /out:"$(OUTDIR)/lmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\lmk.obj" \
	"$(INTDIR)\lmkErr.obj" \
	"$(INTDIR)\lmkList.obj" \
	"$(INTDIR)\lmkParse.obj" \
	"$(INTDIR)\lmkPaSema.obj" \
	"$(INTDIR)\lmkScan.obj" \
	"$(INTDIR)\lmkScSema.obj" \
	"$(INTDIR)\lmkTab.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\lmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"

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

ALL : "$(OUTDIR)\lmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\lmk.obj"
	-@erase "$(INTDIR)\lmkErr.obj"
	-@erase "$(INTDIR)\lmkList.obj"
	-@erase "$(INTDIR)\lmkParse.obj"
	-@erase "$(INTDIR)\lmkPaSema.obj"
	-@erase "$(INTDIR)\lmkScan.obj"
	-@erase "$(INTDIR)\lmkScSema.obj"
	-@erase "$(INTDIR)\lmkTab.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\lmk.exe"
	-@erase "$(OUTDIR)\lmk.ilk"
	-@erase "$(OUTDIR)\lmk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\tmk" /I "..\license" /I "..\imp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\tmk" /I "..\license" /I\
 "..\imp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /Fp"$(INTDIR)/lmk.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/lmk.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/lmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\lmk.obj" \
	"$(INTDIR)\lmkErr.obj" \
	"$(INTDIR)\lmkList.obj" \
	"$(INTDIR)\lmkParse.obj" \
	"$(INTDIR)\lmkPaSema.obj" \
	"$(INTDIR)\lmkScan.obj" \
	"$(INTDIR)\lmkScSema.obj" \
	"$(INTDIR)\lmkTab.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\lmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lmk - Win32 Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "lmk___Wi"
# PROP BASE Intermediate_Dir "lmk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\lmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\lmk.obj"
	-@erase "$(INTDIR)\lmkErr.obj"
	-@erase "$(INTDIR)\lmkList.obj"
	-@erase "$(INTDIR)\lmkParse.obj"
	-@erase "$(INTDIR)\lmkPaSema.obj"
	-@erase "$(INTDIR)\lmkScan.obj"
	-@erase "$(INTDIR)\lmkScSema.obj"
	-@erase "$(INTDIR)\lmkTab.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(OUTDIR)\lmk.exe"
	-@erase "$(OUTDIR)\lmk.ilk"
	-@erase "$(OUTDIR)\lmk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\tmk" /I "..\license" /I "..\imp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\tmk" /I "..\license" /I "..\imp" /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\tmk" /I "..\license" /I\
 "..\imp" /D "_DEBUG" /D "TMTEST" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)/lmk.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/lmk.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/lmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\lmk.obj" \
	"$(INTDIR)\lmkErr.obj" \
	"$(INTDIR)\lmkList.obj" \
	"$(INTDIR)\lmkParse.obj" \
	"$(INTDIR)\lmkPaSema.obj" \
	"$(INTDIR)\lmkScan.obj" \
	"$(INTDIR)\lmkScSema.obj" \
	"$(INTDIR)\lmkTab.obj" \
	"$(INTDIR)\version.obj"

"$(OUTDIR)\lmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "lmk___Wi"
# PROP BASE Intermediate_Dir "lmk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "lmk___Wi"
# PROP Intermediate_Dir "lmk___Wi"
# PROP Target_Dir ""
OUTDIR=.\lmk___Wi
INTDIR=.\lmk___Wi

ALL : ".\lmk.exe"

CLEAN : 
	-@erase "$(INTDIR)\lmk.obj"
	-@erase "$(INTDIR)\lmkErr.obj"
	-@erase "$(INTDIR)\lmkList.obj"
	-@erase "$(INTDIR)\lmkParse.obj"
	-@erase "$(INTDIR)\lmkPaSema.obj"
	-@erase "$(INTDIR)\lmkScan.obj"
	-@erase "$(INTDIR)\lmkScSema.obj"
	-@erase "$(INTDIR)\lmkTab.obj"
	-@erase "$(INTDIR)\version.obj"
	-@erase ".\lmk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\tmk" /I "..\license" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\tmk" /I "..\license" /I "..\imp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AMOSDEV" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\tmk" /I "..\license" /I "..\imp" /D\
 "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AMOSDEV" /Fp"$(INTDIR)/lmk.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\lmk___Wi/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lmk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"lmk.exe"
LINK32_FLAGS=..\license\license.lib ..\imp\implib.lib ..\tmk\tmklib.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/lmk.pdb" /machine:I386\
 /out:"lmk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\lmk.obj" \
	"$(INTDIR)\lmkErr.obj" \
	"$(INTDIR)\lmkList.obj" \
	"$(INTDIR)\lmkParse.obj" \
	"$(INTDIR)\lmkPaSema.obj" \
	"$(INTDIR)\lmkScan.obj" \
	"$(INTDIR)\lmkScSema.obj" \
	"$(INTDIR)\lmkTab.obj" \
	"$(INTDIR)\version.obj"

".\lmk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "lmk - Win32 Release"
# Name "lmk - Win32 Debug"
# Name "lmk - Win32 Test"
# Name "lmk - Win32 AMOS"

!IF  "$(CFG)" == "lmk - Win32 Release"

!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"

!ELSEIF  "$(CFG)" == "lmk - Win32 Test"

!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\version.c
DEP_CPP_VERSI=\
	".\version.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkErr.c
DEP_CPP_LMKER=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	".\lmkScan.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkErr.obj" : $(SOURCE) $(DEP_CPP_LMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkErr.obj" : $(SOURCE) $(DEP_CPP_LMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkErr.obj" : $(SOURCE) $(DEP_CPP_LMKER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkErr.obj" : $(SOURCE) $(DEP_CPP_LMKER) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkList.c
DEP_CPP_LMKLI=\
	"..\tmk\tmkCommon.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkList.obj" : $(SOURCE) $(DEP_CPP_LMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkList.obj" : $(SOURCE) $(DEP_CPP_LMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkList.obj" : $(SOURCE) $(DEP_CPP_LMKLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkList.obj" : $(SOURCE) $(DEP_CPP_LMKLI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkParse.c
DEP_CPP_LMKPA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkParse.h"\
	".\lmkScan.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkParse.obj" : $(SOURCE) $(DEP_CPP_LMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkParse.obj" : $(SOURCE) $(DEP_CPP_LMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkParse.obj" : $(SOURCE) $(DEP_CPP_LMKPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkParse.obj" : $(SOURCE) $(DEP_CPP_LMKPA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkPaSema.c
DEP_CPP_LMKPAS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	".\lmkScan.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkPaSema.obj" : $(SOURCE) $(DEP_CPP_LMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkPaSema.obj" : $(SOURCE) $(DEP_CPP_LMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkPaSema.obj" : $(SOURCE) $(DEP_CPP_LMKPAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkPaSema.obj" : $(SOURCE) $(DEP_CPP_LMKPAS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkScan.c
DEP_CPP_LMKSC=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkScan.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkScan.obj" : $(SOURCE) $(DEP_CPP_LMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkScan.obj" : $(SOURCE) $(DEP_CPP_LMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkScan.obj" : $(SOURCE) $(DEP_CPP_LMKSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkScan.obj" : $(SOURCE) $(DEP_CPP_LMKSC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkScSema.c
DEP_CPP_LMKSCS=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkScan.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkScSema.obj" : $(SOURCE) $(DEP_CPP_LMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkScSema.obj" : $(SOURCE) $(DEP_CPP_LMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkScSema.obj" : $(SOURCE) $(DEP_CPP_LMKSCS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkScSema.obj" : $(SOURCE) $(DEP_CPP_LMKSCS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmkTab.c
DEP_CPP_LMKTA=\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkScan.h"\
	

!IF  "$(CFG)" == "lmk - Win32 Release"


"$(INTDIR)\lmkTab.obj" : $(SOURCE) $(DEP_CPP_LMKTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"


"$(INTDIR)\lmkTab.obj" : $(SOURCE) $(DEP_CPP_LMKTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"


"$(INTDIR)\lmkTab.obj" : $(SOURCE) $(DEP_CPP_LMKTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"


"$(INTDIR)\lmkTab.obj" : $(SOURCE) $(DEP_CPP_LMKTA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmk.c

!IF  "$(CFG)" == "lmk - Win32 Release"

DEP_CPP_LMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	".\lmkParse.h"\
	".\lmkScan.h"\
	".\version.h"\
	

"$(INTDIR)\lmk.obj" : $(SOURCE) $(DEP_CPP_LMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Debug"

DEP_CPP_LMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	".\lmkParse.h"\
	".\version.h"\
	

"$(INTDIR)\lmk.obj" : $(SOURCE) $(DEP_CPP_LMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 Test"

DEP_CPP_LMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	".\lmkParse.h"\
	".\lmkScan.h"\
	".\version.h"\
	

"$(INTDIR)\lmk.obj" : $(SOURCE) $(DEP_CPP_LMK_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lmk - Win32 AMOS"

DEP_CPP_LMK_C=\
	"..\imp\impMacro.h"\
	"..\license\license.h"\
	"..\tmk\tmk.h"\
	"..\tmk\tmkCommon.h"\
	".\lmk_i.h"\
	".\lmkCommon.h"\
	".\lmkList.h"\
	".\lmkParse.h"\
	".\lmkScan.h"\
	".\version.h"\
	

"$(INTDIR)\lmk.obj" : $(SOURCE) $(DEP_CPP_LMK_C) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
