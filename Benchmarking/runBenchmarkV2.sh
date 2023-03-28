
# TODO: parameter for 
# Max sparsity? -> Rows * cols / numNonzeros

#   runCPPBenchmark will wait for nextFile (the next matrix) to be downloaded. 
#   if the benchmark is still running - if currentFile still exists, it will wait 
#   for it to finish.
MATRIX_PATH = "./matrices/MM/"
NEXT_FILE = "$(MATRIX_PATH)nextFile.mtx"
CURRENT_FILE = "$(MATRIX_PATH)currentFile.mtx"

runCPPBenchmark() {
    # if next file is not done, wait
    # while [! -f nextFile.rb ] 
    # do
    #     sleep 0.2
    # done

    # if current file is not done, wait
    while [ -f currentFile.rb ] 
    do
        sleep 0.2
    done

    # Then rename it to currentFile.rb
    # mv $(NEXT_FILE) $(CURRENT_FILE)


}

runSSGET(){

#Search the database with 400 <= #rows <= 450 and numerical symmertry >= 0.99
#./ssget -s '[ @rows -ge 400 ] && [ @rows -le 450 ] && [ $(awk "BEGIN{print(@nsym <= 0.99)}") -eq 1 ]'



# decompress the tar.gz file and rename it to nextFile.rb
    ./ssget -t MM -e -i '[ @rows -gt $(numRows) && @cols -gt $(numCols) && @nonzeros -gt $(numNonZeros)]' -> MATRIX_PATH
    # mv *.mtx nextFile.mtx
}



# read parameters
# while [ $# -gt 0 ] 
# do
#     case $1 in
#         "-c")
#             shift
#             numCols=$1
#             ;;
#         "-r")
#             shift
#             numRows=$1
#             ;;
#         "-v")
#             shift
#             numNonZeros=$1
#             ;;
#         "-i")
#             shift
#             numMatrices=$1
#             ;;
#         "-p")
#             shift
#             problemKind=$1
#             ;;
#     esac
#     shift
# done

# echo "Running benchmark with $numCols columns, $numRows rows, $numNonzeros nonzeros, $numMatrices matrices, and \"$problemKind\" problem kind"

# Compiling benchmark
g++ benchmark.cpp -o benchmark
numMatrices=1
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

    id=$(grep -oP '(?<=id: ).*' $MATRIX_PATH)
    echo "id: $id"

    echo "Running C++ benchmark for matrix $id"

    ./benchmark $MATRIX_PATH $id
    rm -r $MATRIX_PATH
done

# Clean up
rm -r matrices/