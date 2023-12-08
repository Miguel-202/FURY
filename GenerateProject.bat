@echo off
setlocal enabledelayedexpansion

:: Set the initial max version to 0
set maxVer=0

:: Loop through all installed Visual Studio versions
for /f "tokens=*" %%a in ('reg query HKLM\SOFTWARE\WOW6432Node\Microsoft\VisualStudio\SxS\VS7 /s') do (
    set key=%%a
    if not "!key!" == "!key:201=!" (
        set ver=!key:~-4!
        if !ver! gtr !maxVer! (
            set maxVer=!ver!
        )
    )
)

::If no version was detected, then assign to default
if %maxVer% == 0 (
    echo No Visual Studio installations found, setting maxVer to 17.
    set maxVer=17
) else (
    echo The latest Visual Studio version is: %maxVer%
)


:: Construct the Visual Studio version string
::set vsVer=vs20%maxVer%
set vsVer=vs2017

:: Call Premake with the detected Visual Studio version
call vendor\bin\premake\premake5.exe !vsVer!

PAUSE
