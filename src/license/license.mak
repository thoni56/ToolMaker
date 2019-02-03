# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=license - Win32 AMOS Debug
!MESSAGE No configuration specified.  Defaulting to license - Win32 AMOS Debug.
!ENDIF 

!IF "$(CFG)" != "license - Win32 Release" && "$(CFG)" !=\
 "license - Win32 Debug" && "$(CFG)" != "license - Win32 AMOS Debug" && "$(CFG)"\
 != "license - Win32 AMOS Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "license.mak" CFG="license - Win32 AMOS Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "license - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "license - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "license - Win32 AMOS Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "license - Win32 AMOS Release" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "license - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "license - Win32 Release"

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

ALL : "$(OUTDIR)\license.lib"

CLEAN : 
	-@erase "$(INTDIR)\licenseClient.obj"
	-@erase "$(INTDIR)\passwd.obj"
	-@erase "$(INTDIR)\readParam.obj"
	-@erase "$(OUTDIR)\license.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)/license.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/license.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/license.lib" 
LIB32_OBJS= \
	"$(INTDIR)\licenseClient.obj" \
	"$(INTDIR)\passwd.obj" \
	"$(INTDIR)\readParam.obj"

"$(OUTDIR)\license.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "license - Win32 Debug"

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

ALL : "$(OUTDIR)\license.lib"

CLEAN : 
	-@erase "$(INTDIR)\licenseClient.obj"
	-@erase "$(INTDIR)\passwd.obj"
	-@erase "$(INTDIR)\readParam.obj"
	-@erase "$(OUTDIR)\license.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)/license.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/license.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/license.lib" 
LIB32_OBJS= \
	"$(INTDIR)\licenseClient.obj" \
	"$(INTDIR)\passwd.obj" \
	"$(INTDIR)\readParam.obj"

"$(OUTDIR)\license.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "license - Win32 AMOS Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "license_"
# PROP BASE Intermediate_Dir "license_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "license_"
# PROP Intermediate_Dir "license_"
# PROP Target_Dir ""
OUTDIR=.\license_
INTDIR=.\license_

ALL : ".\license.lib"

CLEAN : 
	-@erase "$(INTDIR)\licenseClient.obj"
	-@erase "$(INTDIR)\passwd.obj"
	-@erase "$(INTDIR)\readParam.obj"
	-@erase ".\license.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AMOSDEV" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AMOSDEV" /Fp"$(INTDIR)/license.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\license_/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/license.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"license.lib"
LIB32_FLAGS=/nologo /out:"license.lib" 
LIB32_OBJS= \
	"$(INTDIR)\licenseClient.obj" \
	"$(INTDIR)\passwd.obj" \
	"$(INTDIR)\readParam.obj"

".\license.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "license - Win32 AMOS Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "license0"
# PROP BASE Intermediate_Dir "license0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "license0"
# PROP Intermediate_Dir "license0"
# PROP Target_Dir ""
OUTDIR=.\license0
INTDIR=.\license0

ALL : "$(OUTDIR)\license.lib"

CLEAN : 
	-@erase "$(INTDIR)\licenseClient.obj"
	-@erase "$(INTDIR)\passwd.obj"
	-@erase "$(INTDIR)\readParam.obj"
	-@erase "$(OUTDIR)\license.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AMOSDEV" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AMOSDEV" /Fp"$(INTDIR)/license.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\license0/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/license.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/license.lib" 
LIB32_OBJS= \
	"$(INTDIR)\licenseClient.obj" \
	"$(INTDIR)\passwd.obj" \
	"$(INTDIR)\readParam.obj"

"$(OUTDIR)\license.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "license - Win32 Release"
# Name "license - Win32 Debug"
# Name "license - Win32 AMOS Debug"
# Name "license - Win32 AMOS Release"

!IF  "$(CFG)" == "license - Win32 Release"

!ELSEIF  "$(CFG)" == "license - Win32 Debug"

!ELSEIF  "$(CFG)" == "license - Win32 AMOS Debug"

!ELSEIF  "$(CFG)" == "license - Win32 AMOS Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\readParam.c
DEP_CPP_READP=\
	".\common.h"\
	".\readParam.h"\
	

!IF  "$(CFG)" == "license - Win32 Release"


"$(INTDIR)\readParam.obj" : $(SOURCE) $(DEP_CPP_READP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 Debug"


"$(INTDIR)\readParam.obj" : $(SOURCE) $(DEP_CPP_READP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 AMOS Debug"


"$(INTDIR)\readParam.obj" : $(SOURCE) $(DEP_CPP_READP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 AMOS Release"


"$(INTDIR)\readParam.obj" : $(SOURCE) $(DEP_CPP_READP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\passwd.c
DEP_CPP_PASSW=\
	".\passwd.h"\
	

!IF  "$(CFG)" == "license - Win32 Release"


"$(INTDIR)\passwd.obj" : $(SOURCE) $(DEP_CPP_PASSW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 Debug"


"$(INTDIR)\passwd.obj" : $(SOURCE) $(DEP_CPP_PASSW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 AMOS Debug"


"$(INTDIR)\passwd.obj" : $(SOURCE) $(DEP_CPP_PASSW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 AMOS Release"


"$(INTDIR)\passwd.obj" : $(SOURCE) $(DEP_CPP_PASSW) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\licenseClient.c
DEP_CPP_LICEN=\
	".\common.h"\
	".\license.h"\
	".\license_rpc.h"\
	".\passwd.h"\
	".\readParam.h"\
	{$(INCLUDE)}"\sys\types.h"\
	

!IF  "$(CFG)" == "license - Win32 Release"


"$(INTDIR)\licenseClient.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 Debug"


"$(INTDIR)\licenseClient.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 AMOS Debug"


"$(INTDIR)\licenseClient.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "license - Win32 AMOS Release"


"$(INTDIR)\licenseClient.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
