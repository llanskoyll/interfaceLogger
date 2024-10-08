#!/bin/bash

rm -rf build

mkdir build
cd ./build

rm -rf ./CmakeCache.txt
cmake ..
cmake --build  .

cd ../