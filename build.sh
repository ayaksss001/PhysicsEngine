#!/bin/bash
cd build
cmake ..
make
LC_ALL=C ./Sim
