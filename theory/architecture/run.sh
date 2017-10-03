#! /bin/bash

#compile traffic
gcc -o traffic traffic.c

#run traffic
for i in {1..150}
do
    echo $i
    ./traffic Traffic_violations.csv
done
