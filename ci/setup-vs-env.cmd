@echo off
setlocal

:: Use vswhere to locate the installation path for the current image
:: %1 is the version range, e.g. [14.0,15.0) for VS2015, [15.0,16.0) for VS2017, etc.

for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -version %1 -products * -requires Microsoft.Component.MSBuild -property installationPath`) do (
  set VSINSTALL=%%i
)

if not defined VSINSTALL (
  echo Could not find Visual Studio installation for version range %1
  exit /b 1
)

call "%VSINSTALL%\Common7\Tools\VsDevCmd.bat" -arch=amd64
endlocal & set VSINSTALL=%VSINSTALL%
