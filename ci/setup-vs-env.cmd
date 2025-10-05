@echo off
setlocal

set VS_RANGE=%1

if "%APPVEYOR_BUILD_WORKER_IMAGE%"=="Visual Studio 2015" (
  call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat" -arch=amd64
  goto :eof
)

:: For VS2017 and newer, use vswhere
for /f "usebackq tokens=*" %%i in (`
  "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -version %VS_RANGE% -products * -requires Microsoft.Component.MSBuild -property installationPath
`) do (
  set VSINSTALL=%%i
)

if not defined VSINSTALL (
  echo Could not find Visual Studio installation for version range %VS_RANGE%
  exit /b 1
)

call "%VSINSTALL%\Common7\Tools\VsDevCmd.bat" -arch=amd64
endlocal
