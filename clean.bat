@echo off

set _flag=0

:run
del *.vcxproj
del *.vcxproj.*
del *.sln
del *.log
del *.cmake
del CMakeCache.txt
del makefile
del *.a
rmdir /s /q build
rmdir /s /q CMakeFiles
rmdir /s /q x64
rmdir /s /q Release
rmdir /s /q Debug
rmdir /s /q lib
rmdir /s /q ionir.dir
rmdir /s /q bin
rmdir /s /q out

if %_flag% == 0 (
    set _flag=1
    cd test
    goto run
) else (
    set _flag=0
    cd ..
)
