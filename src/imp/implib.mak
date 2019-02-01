# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=implib - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to implib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "implib - Win32 Release" && "$(CFG)" != "implib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "implib.mak" CFG="implib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "implib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "implib - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "implib - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "implib - Win32 Release"

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

ALL : "$(OUTDIR)\implib.lib"

CLEAN : 
	-@erase "c:\temp\implib.lib"
	-@erase ".\bin\timing.obj"
	-@erase ".\bin\impErr.obj"
	-@erase ".\bin\impScan.obj"
	-@erase ".\bin\impPaSema.obj"
	-@erase ".\bin\name.obj"
	-@erase ".\bin\ast.obj"
	-@erase ".\bin\impMacro.obj"
	-@erase ".\bin\impScSema.obj"
	-@erase ".\bin\version.obj"
	-@erase ".\bin\impList.obj"
	-@erase ".\bin\impParse.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)/implib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/implib.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"c:\temp\implib.lib"
LIB32_FLAGS=/nologo /out:"c:\temp\implib.lib" 
LIB32_OBJS= \
	"$(INTDIR)/timing.obj" \
	"$(INTDIR)/impErr.obj" \
	"$(INTDIR)/impScan.obj" \
	"$(INTDIR)/impPaSema.obj" \
	"$(INTDIR)/name.obj" \
	"$(INTDIR)/ast.obj" \
	"$(INTDIR)/impMacro.obj" \
	"$(INTDIR)/impScSema.obj" \
	"$(INTDIR)/version.obj" \
	"$(INTDIR)/impList.obj" \
	"$(INTDIR)/impParse.obj"

"$(OUTDIR)\implib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "implib - Win32 Debug"

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

ALL : ".\implib.lib"

CLEAN : 
	-@erase ".\implib.lib"
	-@erase ".\bin\timing.obj"
	-@erase ".\bin\impErr.obj"
	-@erase ".\bin\impScan.obj"
	-@erase ".\bin\impPaSema.obj"
	-@erase ".\bin\name.obj"
	-@erase ".\bin\ast.obj"
	-@erase ".\bin\impMacro.obj"
	-@erase ".\bin\impScSema.obj"
	-@erase ".\bin\version.obj"
	-@erase ".\bin\impList.obj"
	-@erase ".\bin\impParse.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)/implib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\bin/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/implib.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/implib.lib" 
LIB32_OBJS= \
	"$(INTDIR)/timing.obj" \
	"$(INTDIR)/impErr.obj" \
	"$(INTDIR)/impScan.obj" \
	"$(INTDIR)/impPaSema.obj" \
	"$(INTDIR)/name.obj" \
	"$(INTDIR)/ast.obj" \
	"$(INTDIR)/impMacro.obj" \
	"$(INTDIR)/impScSema.obj" \
	"$(INTDIR)/version.obj" \
	"$(INTDIR)/impList.obj" \
	"$(INTDIR)/impParse.obj"

".\implib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "implib - Win32 Release"
# Name "implib - Win32 Debug"

!IF  "$(CFG)" == "implib - Win32 Release"

!ELSEIF  "$(CFG)" == "implib - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\timing.c
DEP_CPP_TIMIN=\
	".\timing.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impErr.c
DEP_CPP_IMPER=\
	".\ast.h"\
	".\impCommon.h"\
	".\impErr.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\impScan.h"\
	

"$(INTDIR)\impErr.obj" : $(SOURCE) $(DEP_CPP_IMPER) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impList.c
DEP_CPP_IMPLI=\
	".\impCommon.h"\
	".\impList.h"\
	

"$(INTDIR)\impList.obj" : $(SOURCE) $(DEP_CPP_IMPLI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impMacro.c
DEP_CPP_IMPMA=\
	".\ast.h"\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\impScan.h"\
	".\name.h"\
	".\timing.h"\
	".\version.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\impMacro.obj" : $(SOURCE) $(DEP_CPP_IMPMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impParse.c
DEP_CPP_IMPPA=\
	".\ast.h"\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\impParse.h"\
	".\impScan.h"\
	

"$(INTDIR)\impParse.obj" : $(SOURCE) $(DEP_CPP_IMPPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impPaSema.c
DEP_CPP_IMPPAS=\
	".\ast.h"\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\impScan.h"\
	

"$(INTDIR)\impPaSema.obj" : $(SOURCE) $(DEP_CPP_IMPPAS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impScan.c
DEP_CPP_IMPSC=\
	".\impCommon.h"\
	".\impScan.h"\
	

"$(INTDIR)\impScan.obj" : $(SOURCE) $(DEP_CPP_IMPSC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\impScSema.c
DEP_CPP_IMPSCS=\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\impScan.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\impScSema.obj" : $(SOURCE) $(DEP_CPP_IMPSCS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\name.c
DEP_CPP_NAME_=\
	".\ast.h"\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\impScan.h"\
	".\name.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\name.obj" : $(SOURCE) $(DEP_CPP_NAME_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ast.c
DEP_CPP_AST_C=\
	".\ast.h"\
	".\impCommon.h"\
	".\impList.h"\
	".\impMacro.h"\
	".\name.h"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	

"$(INTDIR)\ast.obj" : $(SOURCE) $(DEP_CPP_AST_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\version.c
DEP_CPP_VERSI=\
	".\version.h"\
	

"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
