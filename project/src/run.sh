#!/bin/bash

cd ./data_ser
rm *
cd ..
cd ./out
rm *
cd ..

gcc -o updatePositions_serial ./update_position.c -lm
./updatePositions_serial ./init/sSystem.txt 200 1
python visualizer.py ./data_ser/
