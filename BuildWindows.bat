@echo off

tools\Windows\premake5 vs2022

call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

set SOLUTION_PATH=KingdomEngine.sln

set CONFIGURATION=Release
set PLATFORM=x64

msbuild %SOLUTION_PATH% /p:Configuration=%CONFIGURATION% /p:Platform=%PLATFORM%

pause
