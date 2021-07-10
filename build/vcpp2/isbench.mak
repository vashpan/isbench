# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "isbench.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/isbench.exe $(OUTDIR)/isbench.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /c
# ADD CPP /nologo /W3 /GX /YX /O2 /I "..\..\src" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /c
CPP_PROJ=/nologo /W3 /GX /YX /O2 /I "..\..\src" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"isbench.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"isbench.bsc" 
BSC32_SBRS= \
	$(INTDIR)/main.sbr \
	$(INTDIR)/utils.sbr \
	$(INTDIR)/bench.sbr \
	$(INTDIR)/winmain.sbr \
	$(INTDIR)/platform.sbr

$(OUTDIR)/isbench.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:console /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:console /MACHINE:I386
# SUBTRACT LINK32 /NODEFAULTLIB
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO\
 /SUBSYSTEM:console /INCREMENTAL:no /PDB:$(OUTDIR)/"isbench.pdb" /MACHINE:I386\
 /OUT:$(OUTDIR)/"isbench.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/main.obj \
	$(INTDIR)/utils.obj \
	$(INTDIR)/bench.obj \
	$(INTDIR)/winmain.obj \
	$(INTDIR)/platform.obj

$(OUTDIR)/isbench.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/isbench.exe $(OUTDIR)/isbench.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /c
# ADD CPP /nologo /W3 /GX /Zi /YX /Od /I "..\..\src" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /c
CPP_PROJ=/nologo /W3 /GX /Zi /YX /Od /I "..\..\src" /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"isbench.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"isbench.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"isbench.bsc" 
BSC32_SBRS= \
	$(INTDIR)/main.sbr \
	$(INTDIR)/utils.sbr \
	$(INTDIR)/bench.sbr \
	$(INTDIR)/winmain.sbr \
	$(INTDIR)/platform.sbr

$(OUTDIR)/isbench.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:console /DEBUG /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:console /DEBUG /MACHINE:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO\
 /SUBSYSTEM:console /INCREMENTAL:yes /PDB:$(OUTDIR)/"isbench.pdb" /DEBUG\
 /MACHINE:I386 /OUT:$(OUTDIR)/"isbench.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/main.obj \
	$(INTDIR)/utils.obj \
	$(INTDIR)/bench.obj \
	$(INTDIR)/winmain.obj \
	$(INTDIR)/platform.obj

$(OUTDIR)/isbench.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Group "Main"

################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\platform.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\main.c

$(INTDIR)/main.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
# End Group
################################################################################
# Begin Group "Benchmarks"

################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\utils.c

$(INTDIR)/utils.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\utils.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench.c

$(INTDIR)/bench.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
# End Group
################################################################################
# Begin Group "Platform"

################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\platform\pstdint.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\platform\win32\winmain.c
DEP_WINMA=\
	\USERS\KONRAD\PROJECTS\isbench\src\platform.h

$(INTDIR)/winmain.obj :  $(SOURCE)  $(DEP_WINMA) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\platform\win32\platform.c
DEP_PLATF=\
	\USERS\KONRAD\PROJECTS\isbench\src\platform.h

$(INTDIR)/platform.obj :  $(SOURCE)  $(DEP_PLATF) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
# End Group
# End Project
################################################################################
