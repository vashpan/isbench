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

ALL : .\WinRel\isbench.exe .\WinRel\isbench.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /ML /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /c
# ADD CPP /nologo /ML /W3 /GX /YX /O2 /I "..\..\src" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /c
CPP_PROJ=/nologo /ML /W3 /GX /YX /O2 /I "..\..\src" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"isbench.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"isbench.bsc" 
BSC32_SBRS= \
	.\WinRel\main.sbr \
	.\WinRel\rle.sbr \
	.\WinRel\qsort.sbr \
	.\WinRel\wc.sbr \
	.\WinRel\utils.sbr \
	.\WinRel\rand.sbr \
	.\WinRel\crc32.sbr \
	.\WinRel\winmain.sbr \
	.\WinRel\platform.sbr

.\WinRel\isbench.bsc : $(OUTDIR)  $(BSC32_SBRS)
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
	.\WinRel\main.obj \
	.\WinRel\rle.obj \
	.\WinRel\qsort.obj \
	.\WinRel\wc.obj \
	.\WinRel\utils.obj \
	.\WinRel\rand.obj \
	.\WinRel\crc32.obj \
	.\WinRel\winmain.obj \
	.\WinRel\platform.obj

.\WinRel\isbench.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : .\WinDebug\isbench.exe .\WinDebug\isbench.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /ML /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /c
# ADD CPP /nologo /ML /W3 /GX /Zi /YX /Od /I "..\..\src" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /c
CPP_PROJ=/nologo /ML /W3 /GX /Zi /YX /Od /I "..\..\src" /D "WIN32" /D "_DEBUG"\
 /D "_CONSOLE" /FR$(INTDIR)/ /Fp$(OUTDIR)/"isbench.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"isbench.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"isbench.bsc" 
BSC32_SBRS= \
	.\WinDebug\main.sbr \
	.\WinDebug\rle.sbr \
	.\WinDebug\qsort.sbr \
	.\WinDebug\wc.sbr \
	.\WinDebug\utils.sbr \
	.\WinDebug\rand.sbr \
	.\WinDebug\crc32.sbr \
	.\WinDebug\winmain.sbr \
	.\WinDebug\platform.sbr

.\WinDebug\isbench.bsc : $(OUTDIR)  $(BSC32_SBRS)
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
	.\WinDebug\main.obj \
	.\WinDebug\rle.obj \
	.\WinDebug\qsort.obj \
	.\WinDebug\wc.obj \
	.\WinDebug\utils.obj \
	.\WinDebug\rand.obj \
	.\WinDebug\crc32.obj \
	.\WinDebug\winmain.obj \
	.\WinDebug\platform.obj

.\WinDebug\isbench.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\main.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\main.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Benchmarks"

################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\rle.c

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\rle.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\rle.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\crc32.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\rle.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\qsort.c

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\qsort.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\qsort.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\qsort.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\wc.c

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\wc.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\wc.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\wc.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\result.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\utils.c

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\utils.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\utils.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\rand.c

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\rand.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\rand.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\utils.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\rand.h
# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\bench\crc32.c

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\crc32.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\crc32.obj :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

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

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\winmain.obj :  $(SOURCE)  $(DEP_WINMA) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\winmain.obj :  $(SOURCE)  $(DEP_WINMA) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\USERS\KONRAD\PROJECTS\isbench\src\platform\win32\platform.c
DEP_PLATF=\
	\USERS\KONRAD\PROJECTS\isbench\src\platform.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\platform.obj :  $(SOURCE)  $(DEP_PLATF) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\platform.obj :  $(SOURCE)  $(DEP_PLATF) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
