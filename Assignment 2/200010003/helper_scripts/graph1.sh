#!/bin/bash

# goal: graph of N vs avg_LU

rm -rf output/output1.out;
make clean;
make fabric;

start=$(date +%s)
path="output/output1.out"

echo -en "2\t" >> $path ; ./main.o -B 2 -N 4 -queue INQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 8 -queue INQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 16 -queue INQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 32 -queue INQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 64 -queue INQ -out $path
echo -en "2\t" >> $path ; ./main.o -B 2 -N 128 -queue INQ -out $path

echo -en "3\t" >> $path ; ./main.o -B 3 -N 4 -queue INQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 8 -queue INQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 16 -queue INQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 32 -queue INQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 64 -queue INQ -out $path
echo -en "3\t" >> $path ; ./main.o -B 3 -N 128 -queue INQ -out $path

echo -en "4\t" >> $path ; ./main.o -B 4 -N 4 -queue INQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 8 -queue INQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 16 -queue INQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 32 -queue INQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 64 -queue INQ -out $path
echo -en "4\t" >> $path ; ./main.o -B 4 -N 128 -queue INQ -out $path

end=$(date +%s)
echo "Elapsed Time: $(($end-$start)) seconds"