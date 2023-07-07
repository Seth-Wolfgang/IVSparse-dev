#!/bin/sh

g++ -w -O2 -I ~/eigen lib/benchmark.cpp -o benchmark

echo "Running Dense Matrix Benchmark"
count=1
#read through each file in denseMatrices/
for file in denseMatrices/*
    do 
    echo $file
    ./benchmark $file $count
    count=$((count+1))
done

echo "Running Sparse Matrix Benchmark"
for file in sparseMatrices/* 
    do 
    echo $file
    ./benchmark $file $count
    count=$((count+1))
done


echo "Done!"

