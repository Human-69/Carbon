@echo off
set configuration=debug
set makeclean=noclean
if "%1"=="clean" set makeclean=clean
if "%2"=="release" set configuration=release 

echo "==== Compiling ImGUI ===="

cd vendor\ImGUI
premake5 gmake
make config=%configuration% || exit \b
cd ..\..

echo "==== Done building ImGUI(%configuration%) ===="
echo.

echo "==== Compiling Carbon ===="

premake5 gmake
if %makeclean%==clean make clean
make config=%configuration% || exit \b

echo "==== Done building Carbon(%configuration%) ===="
echo.

echo "==== Running sandbox ===="
echo.
cd x64/%configuration%
if %configuration%==debug gdb Sandbox.exe
if %configuration%==release Sandbox.exe
echo.
echo "==== Sandbox has exited with code %errorlevel% ===="
cd ../..