#!/bin/sh

g++ iteratorBenchmark.cpp -o iterTest
./iterTest
echo ""
rm iterTest