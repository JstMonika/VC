#!/bin/bash

g++ -std=c++17 $1.cpp -o $1
./$1 < in.txt > out.txt
