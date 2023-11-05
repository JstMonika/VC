#!/bin/bash

g++ -std=c++14 $1.cpp -o $1 -Wall -Wextra -fsanitize=address

rm out.txt

./$1 < in.txt > out.txt
