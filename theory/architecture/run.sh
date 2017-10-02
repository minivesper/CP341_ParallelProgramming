#! /bin/bash

#compile traffic
gcc -o traffic traffic.c

#run traffic
./traffic Traffic_violations.csv
