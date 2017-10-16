#!/bin/bash

gcc -o updatePositions_parallel -lm ./update_position_parallel.c -fopenmp
gcc -o updatePositions_parallel_reduce -lm ./update_position_parallel_reduce.c -fopenmp
gcc -o updatePositions_parallel_withfork -lm ./update_position_parallel_withfork.c -fopenmp
gcc -o updatePositions_serial -lm ./update_position.c
echo 3 bodies 100 timesteps
./updatePositions_serial ./init/sSystem.txt 100 1
./updatePositions_parallel ./init/sSystem.txt 100 1
./updatePositions_parallel_reduce ./init/sSystem.txt 100 1
./updatePositions_parallel_withfork ./init/sSystem.txt 100 1
diff ./data_par/99.txt ./data_ser/99.txt
diff ./data_par_withfork/99.txt ./data_ser/99.txt
echo 600 bodies 100 timesteps
./updatePositions_serial ./init/initState.txt 100 1
./updatePositions_parallel ./init/initState.txt 100 1
./updatePositions_parallel_reduce ./init/initState.txt 100 1
./updatePositions_parallel_withfork ./init/initState.txt 100 1
diff ./data_par/99.txt ./data_ser/99.txt
diff ./data_par_withfork/99.txt ./data_ser/99.txt
echo 6000 bodies 10 timesteps
./updatePositions_serial ./init/huge.txt 10 1
./updatePositions_parallel ./init/huge.txt 10 1
./updatePositions_parallel_reduce ./init/huge.txt 10 1
./updatePositions_parallel_withfork ./init/huge.txt 10 1
diff ./data_par/9.txt ./data_ser/9.txt
diff ./data_par_withfork/9.txt ./data_ser/9.txt
echo 6000 bodies 100 timesteps
./updatePositions_serial ./init/huge.txt 100 1
./updatePositions_parallel ./init/huge.txt 100 1
./updatePositions_parallel_reduce ./init/huge.txt 100 1
./updatePositions_parallel_withfork ./init/huge.txt 100 1
diff ./data_par/99.txt ./data_ser/99.txt
diff ./data_par_withfork/99.txt ./data_ser/99.txt
echo 12000 bodies 10 timesteps
./updatePositions_serial ./init/evenHuger.txt 10 1
./updatePositions_parallel ./init/evenHuger.txt 10 1
./updatePositions_parallel_reduce ./init/evenHuger.txt 10 1
./updatePositions_parallel_withfork ./init/evenHuger.txt 10 1
diff ./data_par/9.txt ./data_ser/9.txt
diff ./data_par_withfork/9.txt ./data_ser/9.txt
echo 100000 bodies 1 timesteps
./updatePositions_serial ./init/stupidBig.txt 1 1
./updatePositions_parallel ./init/stupidBig.txt 1 1
./updatePositions_parallel_reduce ./init/stupidBig.txt 1 1
./updatePositions_parallel_withfork ./init/stupidBig.txt 1 1
diff ./data_par/9.txt ./data_ser/9.txt
diff ./data_par_withfork/9.txt ./data_ser/9.txt
