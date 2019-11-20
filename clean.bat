@echo off
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
