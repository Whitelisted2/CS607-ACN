#!/bin/bash

rm -rf output.txt;
make clean;
make fabric;

./main.o -N 8 -B 4 -p 0.8 -queue INQ -K 0.6 -out output.txt -T 10000
./main.o -N 8 -B 4 -p 0.8 -queue KOUQ -K 0.6 -out output.txt -T 10000
./main.o -N 8 -B 4 -p 0.8 -queue ISLIP -K 0.6 -out output.txt -T 10000
