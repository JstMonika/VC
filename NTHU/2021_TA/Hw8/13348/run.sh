#!/bin/bash

g++ -Wall -Wextra sol.c -g -O2 -o sol -std=c++17
for ((i = 0; i < $1; i++))
do
    ./sol < generator/in$i.txt > generator/out$i.txt
done
