#!/bin/bash

# goal: for graphs 2, 3

rm -rf output/output2.out
make clean;
make fabric;

start=$(date +%s)
path="output/output2.out"

echo -en "2\t" >> $path ; ./main.o -B 2 -N 4 -queue KOUQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 8 -queue KOUQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 16 -queue KOUQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 32 -queue KOUQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 64 -queue KOUQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 128 -queue KOUQ -out $path

echo -en "3\t" >> $path ; ./main.o -B 3 -N 4 -queue KOUQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 8 -queue KOUQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 16 -queue KOUQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 32 -queue KOUQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 64 -queue KOUQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 128 -queue KOUQ -out $path

echo -en "4\t" >> $path ; ./main.o -B 4 -N 4 -queue KOUQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 8 -queue KOUQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 16 -queue KOUQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 32 -queue KOUQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 64 -queue KOUQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 128 -queue KOUQ -out $path

end=$(date +%s)
echo "Elapsed Time: $(($end-$start)) seconds"