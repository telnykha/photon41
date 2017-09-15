# Microsoft Developer Studio Generated NMAKE File, Based on zlib.dsp
!IF "$(CFG)" == ""
CFG=ZLIB - WIN32 LIB DEBUG
!MESSAGE No configuration specified. Defaulting to ZLIB - WIN32 LIB DEBUG.
!ENDIF 

!IF "$(CFG)" != "zlib - Win32 LIB" && "$(CFG)" != "zlib - Win32 LIB Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "zlib.mak" CFG="ZLIB - WIN32 LIB DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "zlib - Win32 LIB" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "zlib - Win32 LIB"

OUTDIR=.\win32\zlib\lib
INTDIR=.\win32\zlib\lib
# Begin Custom Macros
OutDir=.\win32\zlib\lib
# End Custom Macros

ALL : "$(OUTDIR)\zlib.lib"


CLEAN :
	-@erase "$(INTDIR)\adler32.obj"
	-@erase "$(INTDIR)\compress.obj"
	-@erase "$(INTDIR)\crc32.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\gzio.obj"
	-@erase "$(INTDIR)\infblock.obj"
	-@erase "$(INTDIR)\infcodes.obj"
	-@erase "$(INTDIR)\inffast.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\inftrees.obj"
	-@erase "$(INTDIR)\infutil.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\uncompr.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\zlib.pch"
	-@erase "$(INTDIR)\zutil.obj"
	-@erase "$(OUTDIR)\zlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\zlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\zlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adler32.obj" \
	"$(INTDIR)\compress.obj" \
	"$(INTDIR)\crc32.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\gzio.obj" \
	"$(INTDIR)\infblock.obj" \
	"$(INTDIR)\infcodes.obj" \
	"$(INTDIR)\inffast.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\inftrees.obj" \
	"$(INTDIR)\infutil.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\uncompr.obj" \
	"$(INTDIR)\zutil.obj"

"$(OUTDIR)\zlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

OUTDIR=.\win32\zlib\lib_dbg
INTDIR=.\win32\zlib\lib_dbg
# Begin Custom Macros
OutDir=.\win32\zlib\lib_dbg
# End Custom Macros

ALL : "$(OUTDIR)\zlib.lib"


CLEAN :
	-@erase "$(INTDIR)\adler32.obj"
	-@erase "$(INTDIR)\compress.obj"
	-@erase "$(INTDIR)\crc32.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\gzio.obj"
	-@erase "$(INTDIR)\infblock.obj"
	-@erase "$(INTDIR)\infcodes.obj"
	-@erase "$(INTDIR)\inffast.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\inftrees.obj"
	-@erase "$(INTDIR)\infutil.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\uncompr.obj"
	-@erase "$(INTDIR)\zlib.idb"
	-@erase "$(INTDIR)\zlib.pch"
	-@erase "$(INTDIR)\zlib.pdb"
	-@erase "$(INTDIR)\zutil.obj"
	-@erase "$(OUTDIR)\zlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
CPP_PROJ=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\zlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\zlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adler32.obj" \
	"$(INTDIR)\compress.obj" \
	"$(INTDIR)\crc32.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\gzio.obj" \
	"$(INTDIR)\infblock.obj" \
	"$(INTDIR)\infcodes.obj" \
	"$(INTDIR)\inffast.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\inftrees.obj" \
	"$(INTDIR)\infutil.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\uncompr.obj" \
	"$(INTDIR)\zutil.obj"

"$(OUTDIR)\zlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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
!IF EXISTS("zlib.dep")
!INCLUDE "zlib.dep"
!ELSE 
!MESSAGE Warning: cannot find "zlib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "zlib - Win32 LIB" || "$(CFG)" == "zlib - Win32 LIB Debug"
SOURCE=..\..\..\zlib\adler32.c

"$(INTDIR)\adler32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\zlib\compress.c

"$(INTDIR)\compress.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\zlib\crc32.c

"$(INTDIR)\crc32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\zlib\deflate.c

"$(INTDIR)\deflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\zlib\contrib\asm386\gvmat32c.c
SOURCE=..\..\..\zlib\gzio.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yc"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\gzio.obj"	"$(INTDIR)\zlib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yc"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\gzio.obj"	"$(INTDIR)\zlib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\infblock.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\infblock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\infblock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\infcodes.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\infcodes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\infcodes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\inffast.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\inffast.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\inffast.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\inflate.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\inflate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\inflate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\inftrees.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\inftrees.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\inftrees.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\infutil.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\infutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\infutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\zlib\trees.c

"$(INTDIR)\trees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\zlib\uncompr.c

"$(INTDIR)\uncompr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\zlib\msdos\zlib.rc
SOURCE=..\..\..\zlib\zutil.c

!IF  "$(CFG)" == "zlib - Win32 LIB"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\zutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "zlib - Win32 LIB Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /Fp"$(INTDIR)\zlib.pch" /Yu"zutil.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\zlib" /FD /GZ /c 

"$(INTDIR)\zutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\zlib.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

