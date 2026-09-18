@echo off
setlocal
title PulseCore Builder

echo ======================================================
echo           Building PulseCore Standalone .exe         
echo ======================================================

echo.
echo [1/2] Configuring CMake (Release)...
cmake -B build -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [2/2] Compiling PulseCore.exe...
cmake --build build --config Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build compilation failed!
    pause
    exit /b %ERRORLEVEL%
)

echo.
if exist "build\Release\PulseCore.exe" (
    echo [SUCCESS] Build completed!
    echo Binary: build\Release\PulseCore.exe
    echo.
    echo Launching application...
    start "" "build\Release\PulseCore.exe"
) else (
    echo [ERROR] PulseCore.exe was not found.
)

pause
