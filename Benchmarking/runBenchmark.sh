#!/bin/sh

# echo "Running benchmark with $numCols columns, $numRows rows, $numNonzeros nonzeros, $numMatrices matrices, and \"$problemKind\" problem kind"

# Compiling benchmark
g++ -w benchmark.cpp -o benchmark
numMatrices=100
# Downloading matrices and running benchmark at the same time
for x in $(seq 1 $numMatrices)
do
    # Download matrix
    echo "Downloading matrix $i"
    #TODO establish ssget with proper parameters
    #TODO ensure file downloaded is labeled as "nextFile.rb"

    # ssget -c $numCols -r $numRows -v $numNonzeros -p $problemKind -i $i -f nextFile.rb & runCPPBenchmark
    # runSSGET
    # ./ssget -t MM -e -i '[ @rows -gt $(numRows) && @cols -gt $(numCols) && @nonzeros -gt $(numNonZeros)]' -> MATRIX_PATH
    MATRIX_PATH=$(./ssget -t MM -e -i $x)

    # Grabs the ID here because its easier to do in shell than C
    id=$(grep -oP '(?<=id: ).*' $MATRIX_PATH)
    echo "id: $id"

    echo -e "Running C++ benchmark for matrix ID: \033[0;32m$id\033[0m"

    while [ ! -f $MATRIX_PATH ]; do
        sleep 0.2
    done

    ./benchmark $MATRIX_PATH $id
    # rm -r $MATRIX_PATH
done

# Clean up
# rm -r matrices/