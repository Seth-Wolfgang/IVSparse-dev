# Compressed Sparse Fiber Matrices (CSF)


> **Note:** This is a work in progress. The current version is a prototype and is not ready for production use.

> **Note:** Current development branch is `enlightenment` for those interested in seeing the latest changes and work. Main is updated semi-regularly with new features and the such. 

> **Note:** [Current Trello Board](https://trello.com/b/d59vC6HQ/csf-features)
___

## Abstract
Large amounts of data take time and money to store, process, and compress. As data grows exponentially, we need better, cheaper tools to store and process it. 

The Compressed Sparse Fiber (CSF) format is a way to take advantage of naturally redundant data and store it in a usable way. CSF works very well with redundant data, so much so that preliminary testing shows that we can beat common alternative formats in memory footprint by as much as 50%. 

Our implementation of CSF also has variable compression levels that give the user options to lower this footprint even further at a small performance cost. Through our benchmarking we will collect data on the performance and data usage of our CSF format versus other popular, open-source alternatives, such as Compressed Sparse Column. 

CSF offers a novel solution to storing large amounts of data at little performance cost allowing otherwise bottlenecked systems to solve problems with large amounts of data.

___

## What is CSF?


Consider a dense vector:

```
x = {1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 1, 1, 0, 1};
```

This can be stored in CSC format:

```
x = {1, 2, 1, 2,  1,  1,  1};
i = {0, 4, 6, 9, 10, 11, 13};
```

However, the values are highly redundant and so we can adapt "run-length encoding" for paired vectors. We can order `x` and `i` first by value in `x` and second by value in `i`, then store only unique values in `x` and the runs of these unique values in `j`:

```
x = {1, 2}
j = {5, 2};
i = {0, 6, 10, 11, 13, 4, 9};
```

In vector form:

```
v = {1, 5, 0, 6, 10, 11, 13, 2, 2, 4, 9};
//  /   \  |---------------| |   \ |---|
// value run   indices    value run indices
```

Alternatively, store delimiters (`0`) between runs instead of run lengths:

```
v = {1, 0, 6, 10, 11, 13, 0, 2, 4, 9};
//   |  |--------------|  /   \ |---|
// value    indices  delimiter value indices
```

Each index run is a **fiber**. Fibers may be compressed using compression filters for integer arrays. 

___
## Future / In-Progress Work
* Increasing iterator traversal speed
* Non-Negative Matrix Factorization
* Parallel Optimizations
* GPU Acceleration
* Further BLAS Support
* Faster Scalar and Reduction Operations
* Continued Benchmarking
