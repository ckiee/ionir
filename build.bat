@echo off

mkdir build
cd build
cmake --config ..
cmake ..
cmake --build .
cd ..
