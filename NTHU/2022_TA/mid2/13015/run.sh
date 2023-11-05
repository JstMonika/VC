#!/bin/bash

for ((i = 25626; i <= 25635; i++))
do
    ./sol < $i.in > $i.out2
done
