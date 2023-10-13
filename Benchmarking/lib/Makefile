build: simulatedBench_COO.cpp 
	g++ -O2 --std=c++17 -I ~/eigen simulatedBench_COO.cpp -o a.out

debug: simulatedBench_COO.cpp
	g++ -g --std=c++17 -I ~/eigen simulatedBench_COO.cpp -o a.out

run: a.out
	./a.out matrices/mat_10000_50_values.csv matrices/mat_10000_50_rowinds.csv matrices/mat_10000_50_colptrs.csv 0.0001 0 -1 ~/results/

testrun: a.out
	./a.out matrices/mat_10000_50_values.csv matrices/mat_10000_50_rowinds.csv matrices/temp.csv 0.0001 0 -1
