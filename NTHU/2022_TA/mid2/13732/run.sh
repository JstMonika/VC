#!/bin/bash

for ((i = 1; i <= $1; i++))
do
    ./sol < $i.in > $i.out
done
