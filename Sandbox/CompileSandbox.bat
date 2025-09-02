premake5 gmake
set configuration=debug
if "%1"=="clean" make clean
if "%2" == "release" set configuration=release 
make config=%configuration% || exit /b
echo "==== Finished Building CarbonGL(%configuration%) ===="
echo.
echo.