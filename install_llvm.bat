@echo off

rem Set variables.
set build_dir=build

rem Ensure that CMakeLists.txt exists.
if not exist CMakeLists.txt (
    echo Required file 'CMakeLists.txt' was not found in the current directory. (Are you sure this is the LLVM sources directory?)
) else (
    rem Delete previous build directory if it exists.
    if exist %build_dir% (
        echo Deleting previous build directory.
        rmdir /s /q %build_dir%
    )

    mkdir %build_dir%
    cd %build_dir%

    rem Generate/prepare CMake.
    cmake -G "MinGW Makefiles" .. -DLLVM_BUILD_LLVM_DYLIB=ON -DLLVM_INCLUDE_TESTS=OFF

    rem Build & install.
    cmake -DCMAKE_BUILD_TYPE=Release -j4 --target install --build .

    rem Exit build directory.
    cd ..

    rem Inform of build status.
    if %errorlevel% not equ 0 (
        echo Build seems to have failed.
    )
)
