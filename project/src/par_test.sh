#!/bin/bash

srun gcc -o updatePositions_parallel -lm ./update_position_parallel.c -fopenmp
srun gcc -o updatePositions_serial -lm ./update_position.c
echo 3 bodies 100 timesteps
./updatePositions_serial ./init/sSystem.txt 100 1
./updatePositions_parallel ./init/sSystem.txt 100 1
diff ./data_par/99.txt ./data_ser/99.txt
echo 600 bodies 100 timesteps
./updatePositions_serial ./init/initState.txt 100 1
./updatePositions_parallel ./init/initState.txt 100 1
diff ./data_par/99.txt ./data_ser/99.txt
echo 6000 bodies 10 timesteps
./updatePositions_serial ./init/huge.txt 10 1
./updatePositions_parallel ./init/huge.txt 10 1
diff ./data_par/9.txt ./data_ser/9.txt
