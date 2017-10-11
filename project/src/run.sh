#!/bin/bash

cd ./data
rm *
cd ..
cd ./out
rm *
cd ..

gcc -o updatePositions_serial ./update_position.c -lm
./updatePositions_serial ./init/huge.txt 30 0.1
python visualizer.py ./data
