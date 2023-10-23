#!/bin/bash

# goal: for graphs 

rm -rf output/output9.out
make clean;
make fabric;

start=$(date +%s)
path="output/output9.out"

./main.o -B 4 -N 8 -K 0.6 -p 0.1 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.2 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.3 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.4 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.5 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.6 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.7 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.8 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.9 -queue ISLIP -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 1.0 -queue ISLIP -out $path ;

./main.o -B 4 -N 8 -K 0.6 -p 0.1 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.2 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.3 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.4 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.5 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.6 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.7 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.8 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.9 -queue KOUQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 1.0 -queue KOUQ -out $path ;

./main.o -B 4 -N 8 -K 0.6 -p 0.1 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.2 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.3 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.4 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.5 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.6 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.7 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.8 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 0.9 -queue INQ -out $path ;
./main.o -B 4 -N 8 -K 0.6 -p 1.0 -queue INQ -out $path ;

end=$(date +%s)
echo "Elapsed Time: $(($end-$start)) seconds"