# Compressed Sparse Fiber Compression (CSF) Library

## To Do:

 - Overall
    - Get overall file structure approved
    - Start benchmarking compression levels
    - start benchmarking iterator performance
    - start benchmarking compression performance
    - find out if we work with doubles/floats

 - Constructor
    - implement a non-destructive constructor
    - implement a dedicated eigen constructor instead of just a wrapper
    - implement a deep copy constructor for CSF sparse matrices
    - find way to go back to eigen from CSF
      - CSC (triplet) is easy to eigen! (I think)
    - way to get from CSC to CSF and back (quickly)

 - Iterator
    - template out compression levels for different iterators
    - implement iterator into new file structure