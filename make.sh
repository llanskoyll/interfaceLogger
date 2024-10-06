#!/bin/bash

mkdir build
cd ./build
rm -rf ./CmakeCache.txt
cmake ..
cmake --build  .
cd ../