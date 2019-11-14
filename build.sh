#!/bin/sh
mkdir -p build
cd build
cmake --config ..
cmake ..
cmake --build .
cd ..
