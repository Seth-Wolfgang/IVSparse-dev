#!/bin/sh

# TODO: parameter for 
# Max sparsity? -> Rows * cols / numNonzeros

#   runCPPBenchmark will wait for nextFile (the next matrix) to be downloaded. 
#   if the benchmark is still running - if currentFile still exists, it will wait 
#   for it to finish.

runCPPBenchmark() {
    # if next file is not done, wait
    while [! -f nextFile.rb ] 
    do
        sleep 0.2
    done

    # if current file is not done, wait
    while [ -f currentFile.rb ] 
    do
        sleep 0.2
    done

    # Then rename it to currentFile.rb
    mv nextFile.rb currentFile.rb

    id=$(grep -oP '(?<=id: ).*' currentFile.rb)
    echo "id: $id"

    echo "Running C++ benchmark for matrix $id"

    ./runBenchmark.sh currentFile.mtx $id
    rm currentFile.mtx 
}

runSSGET(){


# decompress the tar.gz file and rename it to nextFile.rb
    # tar -xzf *.tar.gz
    # rm nextFile.tar.gz
    # mv *.mtx nextFile.mtx
}



# read parameters
while [ $# -gt 0 ] 
do
    case $1 in
        "-c")
            shift
            numCols=$1
            ;;
        "-r")
            shift
            numRows=$1
            ;;
        "-v")
            shift
            numNonzeros=$1
            ;;
        "-i")
            shift
            numMatrices=$1
            ;;
        "-p")
            shift
            problemKind=$1
            ;;
    esac
    shift

done

echo "Running benchmark with $numCols columns, $numRows rows, $numNonzeros nonzeros, $numMatrices matrices, and \"$problemKind\" problem kind"

# Compiling benchmark
g++ benchmark.cpp -o benchmark

# Downloading matrices and running benchmark at the same time
for i in $(seq 1 $numMatrices)
do
    # Download matrix
    echo "Downloading matrix $i"
    #TODO establish ssget with proper parameters
    #TODO ensure file downloaded is labeled as "nextFile.rb"

    # ssget -c $numCols -r $numRows -v $numNonzeros -p $problemKind -i $i -f nextFile.rb & runCPPBenchmark
done

# Clean up
rm -r currentFile.*
rm -r nextFile.*
rm -r *.tar.gz