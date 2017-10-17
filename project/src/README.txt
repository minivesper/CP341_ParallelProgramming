to compile:
gcc -o updatePositions_(parallel filename extension) -lm ./update_position_parallel.c -fopenmp

to run:
<binary name> <init filename>  <number of timesteps> <length of timestep>
ex: ./updatePositions_serial ./init/sSystem.txt 100 1

my testing method:
./par_test.sh
**This sruns ./par_test_on_comp.sh which runs a number of different tests and reports the times of all of then. This script also recompiles. required modules (slurm, gcc)
***will not compile on head node.
