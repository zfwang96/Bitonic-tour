#!/bin/sh
start="Statistic starting..."
end="Statistic end."
echo $start
rm -f test.txt
g++ -o input.out random_generate.cpp
echo $2 > test.txt
echo $1 $2 $3 > para.txt
./input.out > test.txt < para.txt
g++ -o result.out merge.cpp
./result.out < test.txt
rm -f input.out result.out para.txt
echo $end
