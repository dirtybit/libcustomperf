#!/bin/bash
for i in 10 100 1000 10000 100000 1000000 10000000 
do
    for j in {1..5}
    do
	echo "sample_profile $i times run $j"
	sudo LD_LIBRARY_PATH=../ ../../build/perf stat -e cycles,instructions -as ./sample_profile $i > /dev/null 2> ./results/profile_${i}_${j}.out
    done
done

for i in {1..5}
do
    echo "sample run $i"
    sudo LD_LIBRARY_PATH=../ ../../build/perf stat -e cycles,instructions -a ./sample 2> ./results/sample_${i}.out > /dev/null
done

