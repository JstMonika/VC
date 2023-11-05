#!/bin/bash
g++ -Wall -Wextra sol.c -g -O0 -o sol -std=c++17
./sol < ./generator/in0.txt > ./generator/out0.txt
./sol < ./generator/in1.txt > ./generator/out1.txt
./sol < ./generator/in2.txt > ./generator/out2.txt
./sol < ./generator/in3.txt > ./generator/out3.txt
./sol < ./generator/in4.txt > ./generator/out4.txt
./sol < ./generator/in5.txt > ./generator/out5.txt