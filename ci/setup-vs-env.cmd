@echo off
setlocal

if "%APPVEYOR_BUILD_WORKER_IMAGE%"=="Visual Studio 2015" (
  call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat" -arch=amd64
  goto :eof
)

if "%APPVEYOR_BUILD_WORKER_IMAGE%"=="Visual Studio 2017" (
  call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat" -arch=amd64
  goto :eof
)

if "%APPVEYOR_BUILD_WORKER_IMAGE%"=="Visual Studio 2019" (
  call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat" -arch=amd64
  goto :eof
)

if "%APPVEYOR_BUILD_WORKER_IMAGE%"=="Visual Studio 2022" (
  call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=amd64
  goto :eof
)

echo Unknown image: %APPVEYOR_BUILD_WORKER_IMAGE%
exit /b 1
