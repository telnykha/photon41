# Microsoft Developer Studio Generated NMAKE File, Based on libpng.dsp
!IF "$(CFG)" == ""
CFG=LIBPNG - WIN32 LIB DEBUG
!MESSAGE No configuration specified. Defaulting to LIBPNG - WIN32 LIB DEBUG.
!ENDIF 

!IF "$(CFG)" != "libpng - Win32 LIB" && "$(CFG)" != "libpng - Win32 LIB Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libpng.mak" CFG="LIBPNG - WIN32 LIB DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libpng - Win32 LIB" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libpng - Win32 LIB"

OUTDIR=.\win32\libpng\lib
INTDIR=.\win32\libpng\lib
# Begin Custom Macros
OutDir=.\win32\libpng\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\libpng.lib"

!ELSE 

ALL : "zlib - Win32 LIB" "$(OUTDIR)\libpng.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"zlib - Win32 LIBCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\libpng.idb"
	-@erase "$(INTDIR)\libpng.pch"
	-@erase "$(INTDIR)\png.obj"
	-@erase "$(INTDIR)\pngerror.obj"
	-@erase "$(INTDIR)\pngget.obj"
	-@erase "$(INTDIR)\pngmem.obj"
	-@erase "$(INTDIR)\pngpread.obj"
	-@erase "$(INTDIR)\pngread.obj"
	-@erase "$(INTDIR)\pngrio.obj"
	-@erase "$(INTDIR)\pngrtran.obj"
	-@erase "$(INTDIR)\pngrutil.obj"
	-@erase "$(INTDIR)\pngset.obj"
	-@erase "$(INTDIR)\pngtrans.obj"
	-@erase "$(INTDIR)\pngwio.obj"
	-@erase "$(INTDIR)\pngwrite.obj"
	-@erase "$(INTDIR)\pngwtran.obj"
	-@erase "$(INTDIR)\pngwutil.obj"
	-@erase "$(OUTDIR)\libpng.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /I "..\.." /I "..\..\..\zlib" /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\libpng.pch" /Yu"png.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\libpng" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libpng.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libpng.lib" 
LIB32_OBJS= \
	"$(INTDIR)\png.obj" \
	"$(INTDIR)\pngerror.obj" \
	"$(INTDIR)\pngget.obj" \
	"$(INTDIR)\pngmem.obj" \
	"$(INTDIR)\pngpread.obj" \
	"$(INTDIR)\pngread.obj" \
	"$(INTDIR)\pngrio.obj" \
	"$(INTDIR)\pngrtran.obj" \
	"$(INTDIR)\pngrutil.obj" \
	"$(INTDIR)\pngset.obj" \
	"$(INTDIR)\pngtrans.obj" \
	"$(INTDIR)\pngwio.obj" \
	"$(INTDIR)\pngwrite.obj" \
	"$(INTDIR)\pngwtran.obj" \
	"$(INTDIR)\pngwutil.obj" \
	".\win32\zlib\lib\zlib.lib"

"$(OUTDIR)\libpng.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libpng - Win32 LIB Debug"

OUTDIR=.\win32\libpng\lib_dbg
INTDIR=.\win32\libpng\lib_dbg
# Begin Custom Macros
OutDir=.\win32\libpng\lib_dbg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\libpng.lib"

!ELSE 

ALL : "zlib - Win32 LIB Debug" "$(OUTDIR)\libpng.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"zlib - Win32 LIB DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\libpng.idb"
	-@erase "$(INTDIR)\libpng.pch"
	-@erase "$(INTDIR)\libpng.pdb"
	-@erase "$(INTDIR)\png.obj"
	-@erase "$(INTDIR)\pngerror.obj"
	-@erase "$(INTDIR)\pngget.obj"
	-@erase "$(INTDIR)\pngmem.obj"
	-@erase "$(INTDIR)\pngpread.obj"
	-@erase "$(INTDIR)\pngread.obj"
	-@erase "$(INTDIR)\pngrio.obj"
	-@erase "$(INTDIR)\pngrtran.obj"
	-@erase "$(INTDIR)\pngrutil.obj"
	-@erase "$(INTDIR)\pngset.obj"
	-@erase "$(INTDIR)\pngtrans.obj"
	-@erase "$(INTDIR)\pngwio.obj"
	-@erase "$(INTDIR)\pngwrite.obj"
	-@erase "$(INTDIR)\pngwtran.obj"
	-@erase "$(INTDIR)\pngwutil.obj"
	-@erase "$(OUTDIR)\libpng.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
CPP_PROJ=/nologo /MLd /W3 /Zi /Od /I "..\.." /I "..\..\..\zlib" /D "DEBUG" /D "_DEBUG" /D PNG_DEBUG=1 /D "WIN32" /Fp"$(INTDIR)\libpng.pch" /Yu"png.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\libpng" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libpng.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\libpng.lib" 
LIB32_OBJS= \
	"$(INTDIR)\png.obj" \
	"$(INTDIR)\pngerror.obj" \
	"$(INTDIR)\pngget.obj" \
	"$(INTDIR)\pngmem.obj" \
	"$(INTDIR)\pngpread.obj" \
	"$(INTDIR)\pngread.obj" \
	"$(INTDIR)\pngrio.obj" \
	"$(INTDIR)\pngrtran.obj" \
	"$(INTDIR)\pngrutil.obj" \
	"$(INTDIR)\pngset.obj" \
	"$(INTDIR)\pngtrans.obj" \
	"$(INTDIR)\pngwio.obj" \
	"$(INTDIR)\pngwrite.obj" \
	"$(INTDIR)\pngwtran.obj" \
	"$(INTDIR)\pngwutil.obj" \
	".\win32\zlib\lib_dbg\zlib.lib"

"$(OUTDIR)\libpng.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("libpng.dep")
!INCLUDE "libpng.dep"
!ELSE 
!MESSAGE Warning: cannot find "libpng.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "libpng - Win32 LIB" || "$(CFG)" == "libpng - Win32 LIB Debug"
SOURCE=..\..\png.c

!IF  "$(CFG)" == "libpng - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /I "..\.." /I "..\..\..\zlib" /D "WIN32" /D "NDEBUG" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\libpng" /FD /c 

"$(INTDIR)\png.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "libpng - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /I "..\.." /I "..\..\..\zlib" /D "DEBUG" /D "_DEBUG" /D PNG_DEBUG=1 /D "WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\libpng" /FD /GZ /c 

"$(INTDIR)\png.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\png.rc
SOURCE=..\..\pngerror.c

!IF  "$(CFG)" == "libpng - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /I "..\.." /I "..\..\..\zlib" /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\libpng.pch" /Yc"png.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\libpng" /FD /c 

"$(INTDIR)\pngerror.obj"	"$(INTDIR)\libpng.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "libpng - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /I "..\.." /I "..\..\..\zlib" /D "DEBUG" /D "_DEBUG" /D PNG_DEBUG=1 /D "WIN32" /Fp"$(INTDIR)\libpng.pch" /Yc"png.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\libpng" /FD /GZ /c 

"$(INTDIR)\pngerror.obj"	"$(INTDIR)\libpng.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\pngget.c

"$(INTDIR)\pngget.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngmem.c

"$(INTDIR)\pngmem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngpread.c

"$(INTDIR)\pngpread.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngread.c

"$(INTDIR)\pngread.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngrio.c

"$(INTDIR)\pngrio.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngrtran.c

"$(INTDIR)\pngrtran.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngrutil.c

"$(INTDIR)\pngrutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngset.c

"$(INTDIR)\pngset.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngtrans.c

"$(INTDIR)\pngtrans.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngvcrd.c
SOURCE=..\..\pngwio.c

"$(INTDIR)\pngwio.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngwrite.c

"$(INTDIR)\pngwrite.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngwtran.c

"$(INTDIR)\pngwtran.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\pngwutil.c

"$(INTDIR)\pngwutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\libpng.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "libpng - Win32 LIB"

"zlib - Win32 LIB" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 LIB" 
   cd "."

"zlib - Win32 LIBCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 LIB" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "libpng - Win32 LIB Debug"

"zlib - Win32 LIB Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 LIB Debug" 
   cd "."

"zlib - Win32 LIB DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 LIB Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 

