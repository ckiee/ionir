@echo off

cd build
cmake --config ..
cmake ..
cmake --build .
cd ..
