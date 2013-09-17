#!/bin/bash
for i in 10000 50000 100000 500000 1000000 5000000 10000000 
do
    for j in {1..5}
    do
	echo "sample $i times run $j"
	sudo LD_LIBRARY_PATH=../ ../../build/perf stat -e cycles,instructions -as ./profile $i > /dev/null 2>  /dev/null 2> ./results/profile_${i}_${j}.out
    done
done

for i in {1..5}
do
    sudo LD_LIBRARY_PATH=../ ../../build/perf stat -e cycles,instructions -as ./sample 0 > /dev/null 2> ./results/sample_${i}.out
done


