@echo off
set configuration=debug
set makeclean=noclean
if "%1"=="clean" set makeclean=clean
if "%2" == "release" set configuration=release 
cd CarbonCore
echo "Compiling Core"
call CompileCore.bat %makeclean% %configuration% || exit /b
copy "%~dp0CarbonCore\Lib\%configuration%\CarbonCore.lib" "%~dp0Sandbox\lib"
cd ../CarbonGL
echo "Compiling Graphics Library"
call CompileCGL.bat %makeclean% %configuration% || exit /b
copy "%~dp0CarbonGL\Lib\%configuration%\CarbonGL.lib" "%~dp0Sandbox\lib"
cd ../Sandbox
call CompileSandbox.bat || exit /b
echo "==== Running sandbox ===="
echo.
cd bin/%configuration%
Sandbox.exe
echo.
echo "==== Sandbox has exited with code %errorlevel% ===="
cd ../../../