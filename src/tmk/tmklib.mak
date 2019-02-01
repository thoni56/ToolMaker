# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=tmk - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to tmk - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tmk - Win32 Release" && "$(CFG)" != "tmk - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "tmklib.mak" CFG="tmk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tmk - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "tmk - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "tmk - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "tmk - Win32 Release"

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

ALL : "$(OUTDIR)\tmklib.lib"

CLEAN : 
	-@erase "$(INTDIR)\tmkCommon.obj"
	-@erase "$(INTDIR)\tmkErr.obj"
	-@erase "$(INTDIR)\tmkOpts.obj"
	-@erase "$(INTDIR)\tmkParse.obj"
	-@erase "$(INTDIR)\tmkPaSema.obj"
	-@erase "$(INTDIR)\tmkScan.obj"
	-@erase "$(INTDIR)\tmkScSema.obj"
	-@erase "$(OUTDIR)\tmklib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)/tmklib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/tmklib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/tmklib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\tmkCommon.obj" \
	"$(INTDIR)\tmkErr.obj" \
	"$(INTDIR)\tmkOpts.obj" \
	"$(INTDIR)\tmkParse.obj" \
	"$(INTDIR)\tmkPaSema.obj" \
	"$(INTDIR)\tmkScan.obj" \
	"$(INTDIR)\tmkScSema.obj"

"$(OUTDIR)\tmklib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tmk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tmk___Wi"
# PROP BASE Intermediate_Dir "tmk___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
OUTDIR=.\.
INTDIR=.\bin

ALL : "$(OUTDIR)\tmklib.lib"

CLEAN : 
	-@erase "$(INTDIR)\tmkCommon.obj"
	-@erase "$(INTDIR)\tmkErr.obj"
	-@erase "$(INTDIR)\tmkOpts.obj"
	-@erase "$(INTDIR)\tmkParse.obj"
	-@erase "$(INTDIR)\tmkPaSema.obj"
	-@erase "$(INTDIR)\tmkScan.obj"
	-@erase "$(INTDIR)\tmkScSema.obj"
	-@erase "$(OUTDIR)\tmklib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)/tmklib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/tmklib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/tmklib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\tmkCommon.obj" \
	"$(INTDIR)\tmkErr.obj" \
	"$(INTDIR)\tmkOpts.obj" \
	"$(INTDIR)\tmkParse.obj" \
	"$(INTDIR)\tmkPaSema.obj" \
	"$(INTDIR)\tmkScan.obj" \
	"$(INTDIR)\tmkScSema.obj"

"$(OUTDIR)\tmklib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "tmk - Win32 Release"
# Name "tmk - Win32 Debug"

!IF  "$(CFG)" == "tmk - Win32 Release"

!ELSEIF  "$(CFG)" == "tmk - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\tmkCommon.c
DEP_CPP_TMKCO=\
	".\tmk.h"\
	".\tmk_i.h"\
	".\tmkCommon.h"\
	".\tmkParse.h"\
	".\tmkScan.h"\
	

"$(INTDIR)\tmkCommon.obj" : $(SOURCE) $(DEP_CPP_TMKCO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmkOpts.c
DEP_CPP_TMKOP=\
	".\tmk.h"\
	".\tmkCommon.h"\
	".\tmkList.h"\
	".\version.h"\
	

"$(INTDIR)\tmkOpts.obj" : $(SOURCE) $(DEP_CPP_TMKOP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmkParse.c
DEP_CPP_TMKPA=\
	".\tmk.h"\
	".\tmkCommon.h"\
	".\tmkParse.h"\
	".\tmkScan.h"\
	

"$(INTDIR)\tmkParse.obj" : $(SOURCE) $(DEP_CPP_TMKPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmkPaSema.c
DEP_CPP_TMKPAS=\
	".\tmk.h"\
	".\tmk_i.h"\
	".\tmkCommon.h"\
	".\tmkList.h"\
	".\tmkScan.h"\
	

"$(INTDIR)\tmkPaSema.obj" : $(SOURCE) $(DEP_CPP_TMKPAS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmkScan.c
DEP_CPP_TMKSC=\
	".\tmk.h"\
	".\tmk_i.h"\
	".\tmkCommon.h"\
	".\tmkScan.h"\
	

"$(INTDIR)\tmkScan.obj" : $(SOURCE) $(DEP_CPP_TMKSC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmkScSema.c
DEP_CPP_TMKSCS=\
	".\tmk.h"\
	".\tmk_i.h"\
	".\tmkCommon.h"\
	".\tmkScan.h"\
	

"$(INTDIR)\tmkScSema.obj" : $(SOURCE) $(DEP_CPP_TMKSCS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmkErr.c
DEP_CPP_TMKER=\
	".\tmk.h"\
	".\tmkCommon.h"\
	".\tmkList.h"\
	".\tmkScan.h"\
	

"$(INTDIR)\tmkErr.obj" : $(SOURCE) $(DEP_CPP_TMKER) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
