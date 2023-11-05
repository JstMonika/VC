#!/bin/bash

for ((i = 0; i < $1; i++))
do
    ./sol < generator/in$i.txt > generator/out$i.txt
done
