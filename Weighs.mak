# Microsoft Developer Studio Generated NMAKE File, Based on Weighs.dsp
!IF "$(CFG)" == ""
CFG=Weighs - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Weighs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Weighs - Win32 Debug" && "$(CFG)" != "Weighs - Win32 Release MinSize"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Weighs.mak" CFG="Weighs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Weighs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Weighs - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Weighs - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Weighs.dll" "$(OUTDIR)\Weighs.bsc"


CLEAN :
	-@erase "$(INTDIR)\KeybParams.obj"
	-@erase "$(INTDIR)\KeybParams.sbr"
	-@erase "$(INTDIR)\MassaK.obj"
	-@erase "$(INTDIR)\MassaK.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Weighs.obj"
	-@erase "$(INTDIR)\Weighs.pch"
	-@erase "$(INTDIR)\Weighs.res"
	-@erase "$(INTDIR)\Weighs.sbr"
	-@erase "$(OUTDIR)\Weighs.bsc"
	-@erase "$(OUTDIR)\Weighs.dll"
	-@erase "$(OUTDIR)\Weighs.exp"
	-@erase "$(OUTDIR)\Weighs.ilk"
	-@erase "$(OUTDIR)\Weighs.lib"
	-@erase "$(OUTDIR)\Weighs.pdb"
	-@erase ".\Weighs.h"
	-@erase ".\Weighs.tlb"
	-@erase ".\Weighs_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Weighs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Weighs.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Weighs.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MassaK.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Weighs.sbr" \
	"$(INTDIR)\KeybParams.sbr"

"$(OUTDIR)\Weighs.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Weighs.pdb" /debug /machine:I386 /def:".\Weighs.def" /out:"$(OUTDIR)\Weighs.dll" /implib:"$(OUTDIR)\Weighs.lib" /pdbtype:sept 
DEF_FILE= \
	".\Weighs.def"
LINK32_OBJS= \
	"$(INTDIR)\MassaK.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Weighs.obj" \
	"$(INTDIR)\Weighs.res" \
	"$(INTDIR)\KeybParams.obj"

"$(OUTDIR)\Weighs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Weighs - Win32 Release MinSize"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Weighs.dll" ".\Weighs.tlb" ".\Weighs.h" ".\Weighs_i.c" "$(OUTDIR)\Weighs.bsc"


CLEAN :
	-@erase "$(INTDIR)\KeybParams.obj"
	-@erase "$(INTDIR)\KeybParams.sbr"
	-@erase "$(INTDIR)\MassaK.obj"
	-@erase "$(INTDIR)\MassaK.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Weighs.obj"
	-@erase "$(INTDIR)\Weighs.pch"
	-@erase "$(INTDIR)\Weighs.res"
	-@erase "$(INTDIR)\Weighs.sbr"
	-@erase "$(OUTDIR)\Weighs.bsc"
	-@erase "$(OUTDIR)\Weighs.dll"
	-@erase "$(OUTDIR)\Weighs.exp"
	-@erase "$(OUTDIR)\Weighs.lib"
	-@erase ".\Weighs.h"
	-@erase ".\Weighs.tlb"
	-@erase ".\Weighs_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Weighs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Weighs.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Weighs.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MassaK.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Weighs.sbr" \
	"$(INTDIR)\KeybParams.sbr"

"$(OUTDIR)\Weighs.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Weighs.pdb" /machine:I386 /def:".\Weighs.def" /out:"$(OUTDIR)\Weighs.dll" /implib:"$(OUTDIR)\Weighs.lib" 
DEF_FILE= \
	".\Weighs.def"
LINK32_OBJS= \
	"$(INTDIR)\MassaK.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Weighs.obj" \
	"$(INTDIR)\Weighs.res" \
	"$(INTDIR)\KeybParams.obj"

"$(OUTDIR)\Weighs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Weighs.dep")
!INCLUDE "Weighs.dep"
!ELSE 
!MESSAGE Warning: cannot find "Weighs.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Weighs - Win32 Debug" || "$(CFG)" == "Weighs - Win32 Release MinSize"
SOURCE=.\KeybParams.cpp

"$(INTDIR)\KeybParams.obj"	"$(INTDIR)\KeybParams.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Weighs.pch"


SOURCE=.\MassaK.cpp

"$(INTDIR)\MassaK.obj"	"$(INTDIR)\MassaK.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Weighs.pch" ".\Weighs.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Weighs - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Weighs.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Weighs.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Weighs - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Weighs.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Weighs.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Weighs.cpp

"$(INTDIR)\Weighs.obj"	"$(INTDIR)\Weighs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Weighs.pch" ".\Weighs.h" ".\Weighs_i.c"


SOURCE=.\Weighs.idl
MTL_SWITCHES=/tlb ".\Weighs.tlb" /h "Weighs.h" /iid "Weighs_i.c" /Oicf 

".\Weighs.tlb"	".\Weighs.h"	".\Weighs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\Weighs.rc

"$(INTDIR)\Weighs.res" : $(SOURCE) "$(INTDIR)" ".\Weighs.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

