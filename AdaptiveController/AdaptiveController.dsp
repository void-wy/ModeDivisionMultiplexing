# Microsoft Developer Studio Project File - Name="AdaptiveController" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AdaptiveController - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AdaptiveController.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AdaptiveController.mak" CFG="AdaptiveController - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AdaptiveController - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AdaptiveController - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AdaptiveController - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "ICC" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib cxcore.lib cv.lib ml.lib cvaux.lib highgui.lib cvcam.lib CGVideo.lib CGVidEx.lib /nologo /subsystem:console /machine:I386 /libpath:"ICC"

!ELSEIF  "$(CFG)" == "AdaptiveController - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "ICC" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib cxcore.lib cv.lib ml.lib cvaux.lib highgui.lib cvcam.lib CGVideo.lib CGVidEx.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"ICC"

!ENDIF 

# Begin Target

# Name "AdaptiveController - Win32 Release"
# Name "AdaptiveController - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdaptiveController.cpp
# End Source File
# Begin Source File

SOURCE=.\FakeCCD_Constructor.cpp
# End Source File
# Begin Source File

SOURCE=.\FakeCCD_Destructor.cpp
# End Source File
# Begin Source File

SOURCE=.\FakeCCD_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\FakeCCD_Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageProcessing_Constructor.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageProcessing_Destructor.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageProcessing_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageProcessing_Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\RealCCD_Constructor.cpp
# End Source File
# Begin Source File

SOURCE=.\RealCCD_Destructor.cpp
# End Source File
# Begin Source File

SOURCE=.\RealCCD_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\RealCCD_Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\SimulatedAnnealing_Constructor.cpp
# End Source File
# Begin Source File

SOURCE=.\SimulatedAnnealing_Destructor.cpp
# End Source File
# Begin Source File

SOURCE=.\SimulatedAnnealing_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\SimulatedAnnealing_Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\SLM_Constructor.cpp
# End Source File
# Begin Source File

SOURCE=.\SLM_Destructor.cpp
# End Source File
# Begin Source File

SOURCE=.\SLM_Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\SLM_Utility.cpp
# End Source File
# Begin Source File

SOURCE=.\Test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCD.H
# End Source File
# Begin Source File

SOURCE=.\FakeCCD.h
# End Source File
# Begin Source File

SOURCE=.\ImageProcessing.h
# End Source File
# Begin Source File

SOURCE=.\Macros.h
# End Source File
# Begin Source File

SOURCE=.\RealCCD.h
# End Source File
# Begin Source File

SOURCE=.\SimulatedAnnealing.h
# End Source File
# Begin Source File

SOURCE=.\SLM.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
