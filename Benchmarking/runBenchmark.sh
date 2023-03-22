#!/bin/sh

# TODO: parameter for 
# Max sparsity? -> Rows * cols / numNonzeros

#   runCPPBenchmark will wait for nextFile (the next matrix) to be downloaded. 
#   if the benchmark is still running - if currentFile still exists, it will wait 
#   for it to finish.

runCPPBenchmark() {
    # if next file is not done, wait
    while [! -f nextFile.rb ] do
        sleep 0.2
    done

    # if current file is not done, wait
    while [ -f currentFile.rb ] do
        sleep 0.2
    done

    # Then rename it to currentFile.rb
    mv nextFile.rb currentFile.rb
    echo "Running C++ benchmark"
    ./runBenchmark.sh
    rm currentFile.rb 
}

runSSGET(){



}

# read parameters
while [ "$#" -gt 0 ] do
    case "$0" in
        "-c")
            shift
            numCols=$0
            ;;
        "-n")
            shift
            numRows=$0
            ;;
        "-v")
            shift
            numNonzeros=$0
            ;;
        "-i")
            shift
            numMatrices=$0
            ;;
        "-p")
            shift
            problemKind=$0
            ;;
        5)
    esac
    shift
done

