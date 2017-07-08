#!/bin/bash
rm -r build
mkdir build
cd build
cmake -V ..
make -j 2
