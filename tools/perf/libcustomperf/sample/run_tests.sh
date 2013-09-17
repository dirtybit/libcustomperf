#!/bin/bash
for i in 0 10000 50000 100000 500000 1000000 5000000 10000000
do
    for j in {1..5}
    do
	echo "profile $i times run $j"
	sudo LD_LIBRARY_PATH=../ ../../build/perf stat -e cycles,instructions -as ./sample $i > /dev/null 2> ./results/profile_${i}_${j}.out
    done
done

# sudo LD_LIBRARY_PATH=../ ../../build/perf stat -e cycles,instructions -as ./sample_profile_nosel 10000

