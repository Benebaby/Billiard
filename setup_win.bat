@ECHO OFF

setlocal enableextensions enabledelayedexpansion

WHERE cmake
IF ERRORLEVEL == 1 (
	ECHO ERROR: CMake needs to be installed!
	GOTO end
) 
CLS


ECHO Choose the number of your IDE:
ECHO (1) Eclipse CDT mit MinGW
ECHO (2) Sublime Text 2 mit MinGW
ECHO (3) MinGW Makefiles
ECHO (4) VisualStudio2017
ECHO (5) VisualStudio2017 Win64
ECHO (6) VisualStudio2019
ECHO (7) VisualStudio2019 Win64
ECHO ----------------------
CHOICE /n /c "1234567" /M ":"

SET IDECHOICE=%ERRORLEVEL%
IF %IDECHOICE% LEQ 3 (
	ECHO Choose build type:
	ECHO "(1) Debug"
	ECHO "(2) Release"
	ECHO ----------------------
	CHOICE /n /c "12" /M ":"
	SET BUILDTYPE=!ERRORLEVEL!
	IF "!BUILDTYPE!"=="1" ( SET BUILDTYPEEXTENSION=Debug)
	IF "!BUILDTYPE!"=="2" ( SET BUILDTYPEEXTENSION=Release)
)

REM Visualstudio does not allow for outside build type specification, so no suffix is used
IF %IDECHOICE%==7 ( SET GNAME="VisualStudio19Win64"& SET FOLDER="BUILD_WIN_VisualStudio19Win64"&SET GEN="Visual Studio 16 2019" & SET PARAMS=-A x64 & GOTO install )
IF %IDECHOICE%==6 ( SET GNAME="VisualStudio19"& SET FOLDER="BUILD_WIN_VisualStudio19"&SET GEN="Visual Studio 16 2019" & SET PARAMS="-A Win32" & GOTO install )
IF %IDECHOICE%==5 ( SET GNAME="VisualStudio17Win64"& SET FOLDER="BUILD_WIN_VisualStudio17Win64"&SET GEN="Visual Studio 15 2017 Win64"& GOTO install )
IF %IDECHOICE%==4 ( SET GNAME="VisualStudio17"& SET FOLDER="BUILD_WIN_VisualStudio17"&SET GEN="Visual Studio 15 2017"& GOTO install )
IF %IDECHOICE%==3 ( SET GNAME="MinGW_%BUILDTYPEEXTENSION%"& SET FOLDER="BUILD_WIN_MinGW_%BUILDTYPEEXTENSION%"&SET GEN="MinGW Makefiles"& GOTO install )
IF %IDECHOICE%==2 ( SET GNAME="SublimeText2_%BUILDTYPEEXTENSION%"& SET FOLDER="BUILD_WIN_SublimeText2_%BUILDTYPEEXTENSION%"& SET GEN="Sublime Text 2 - MinGW Makefiles"&   SET PARAMS="-DCMAKE_BUILD_TYPE=%BUILDTYPEEXTENSION%"& GOTO install )
IF %IDECHOICE%==1 ( SET GNAME=Eclipse_%BUILDTYPEEXTENSION%& SET FOLDER="BUILD_WIN_Eclipse_%BUILDTYPEEXTENSION%"& SET GEN="Eclipse CDT4 - MinGW Makefiles"&  SET PARAMS=-DCMAKE_BUILD_TYPE=%BUILDTYPEEXTENSION%& GOTO install )
ECHO Something went wrong... 
GOTO end

:install
ECHO Make installable (Shader and resource paths will be set relative to execution)?
ECHO "(1) No"
ECHO "(2) Yes"
ECHO ----------------------
CHOICE /n /c "12" /M ":"
IF %ERRORLEVEL%==2 (
	ECHO Install
	SET PARAMS=%PARAMS% -DMAKE_INSTALLABLE=TRUE -DCMAKE_INSTALL_PREFIX=../INSTALL_WIN_%GNAME%
) ELSE (
	SET PARAMS=%PARAMS% -DMAKE_INSTALLABLE=FALSE
)


:create
mkdir %FOLDER%
cd %FOLDER%
echo cmake -G%GEN% %PARAMS% ../src/
cmake -G%GEN% %PARAMS% ../src/
if "!errorlevel!"=="1" cd.. &echo A CMake error happend. %FOLDER% wasn't created.

:end

endlocal
pause
