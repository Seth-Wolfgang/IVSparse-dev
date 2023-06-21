#!/bin/sh

g++ -w -O2 lib/benchmark.cpp -o benchmark

echo "Running Dense Matrix Benchmark"

#read through each file in denseMatrices/
for file in denseMatrices/*
    do 
    echo $file
    ./benchmark $file 
done

echo "Running Sparse Matrix Benchmark"
for file in sparseMatrices/* 
    do 
    echo $file
    ./benchmark $file
done


echo "Done!"

