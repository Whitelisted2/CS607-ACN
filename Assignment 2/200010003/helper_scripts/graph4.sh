#!/bin/bash

# goal: graph 4

rm -rf output/output4.out
make clean;
make fabric;

start=$(date +%s)
path="output/output4.out"

echo -en "0.6\t" >> $path ; ./main.o -K 0.6 -N 4 -queue KOUQ -out $path
echo -en "0.6\t" >> $path ; ./main.o -K 0.6 -N 8 -queue KOUQ -out $path
echo -en "0.6\t" >> $path ; ./main.o -K 0.6 -N 16 -queue KOUQ -out $path
echo -en "0.6\t" >> $path ; ./main.o -K 0.6 -N 32 -queue KOUQ -out $path
echo -en "0.6\t" >> $path ; ./main.o -K 0.6 -N 64 -queue KOUQ -out $path
echo -en "0.6\t" >> $path ; ./main.o -K 0.6 -N 128 -queue KOUQ -out $path

echo -en "0.8\t" >> $path ; ./main.o -K 0.8 -N 4 -queue KOUQ -out $path
echo -en "0.8\t" >> $path ; ./main.o -K 0.8 -N 8 -queue KOUQ -out $path
echo -en "0.8\t" >> $path ; ./main.o -K 0.8 -N 16 -queue KOUQ -out $path
echo -en "0.8\t" >> $path ; ./main.o -K 0.8 -N 32 -queue KOUQ -out $path
echo -en "0.8\t" >> $path ; ./main.o -K 0.8 -N 64 -queue KOUQ -out $path
echo -en "0.8\t" >> $path ; ./main.o -K 0.8 -N 128 -queue KOUQ -out $path

echo -en "1.0\t" >> $path ; ./main.o -K 1.0 -N 4 -queue KOUQ -out $path
echo -en "1.0\t" >> $path ; ./main.o -K 1.0 -N 8 -queue KOUQ -out $path
echo -en "1.0\t" >> $path ; ./main.o -K 1.0 -N 16 -queue KOUQ -out $path
echo -en "1.0\t" >> $path ; ./main.o -K 1.0 -N 32 -queue KOUQ -out $path
echo -en "1.0\t" >> $path ; ./main.o -K 1.0 -N 64 -queue KOUQ -out $path
echo -en "1.0\t" >> $path ; ./main.o -K 1.0 -N 128 -queue KOUQ -out $path

end=$(date +%s)
echo "Elapsed Time: $(($end-$start)) seconds"