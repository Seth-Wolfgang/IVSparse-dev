@mainpage Overview

## Compressed Sparse Fiber (CSF) Matrix Package

[Github Repo](https://github.com/Seth-Wolfgang/CSF-Matrix)

Large amounts of data take time and money to store, process, and compress. As data grows exponentially, we need better, cheaper tools to store and process it. 

The Compressed Sparse Fiber (CSF) format is a way to take advantage of naturally redundant data and store it in a usable way. CSF works very well with redundant data, so much so that preliminary testing shows that it can beat common alternative formats in memory footprint by as much as 50%. This implementation of CSF also has variable compression levels that give the user options to lower this footprint even further at a small performance cost.

CSF offers a novel solution to storing large amounts of data at little performance cost allowing otherwise bottlenecked systems to solve problems with large amounts of data.


### What is CSF?

Compressed Sparse Fiber is another way to store sparse data much like compressed sparse column (CSC) or coordinate format (COO). The way CSF works is that a matrix is first broken down by major order, most commonly by column, and then by fiber.

After getting an individual column from the original matrix we construct a number of fibers to represent the data in that column. Fibers are simply a value followed by the indices where that value occurs in the column. By doing this for each value we get a column represented by a number of these fibers and then doing this for each column we can store an entire matrix this way.

[Put a picture of CSF here plz skyler]

___


### How does CSF Compress?

There are a few different ways in which CSF compresses data. The first is redundancy, with fibers alone being able to compress redudnant data up to 50% compared to CSC. The second is Positive Delta Encoding, which is a process which we apply to the indices of a fiber which encodes the distance between each index. The third way is through bytepacking, which is when we cast each fiber's indices to the smallest data type that doesn't lose precision.

#### Redundancy

It's easy to see how redundancy can be taken advantage of when looking at CSC format. In this format each value and index must be listed once no matter the data, with a set of column pointers being used to delimit columns. However in CSF if a column has only a single value, it's only stored once and then all of the indices that value is located. This means that in the simplest case of a column 50 long of all ones, CSC needs to store 100 values where as CSF needs only to store 51, the 1 and all the indices. 

Therefore in datasets that are highly redundant CSF mananges to not explicitly store a lot of values resulting in good compression ratios for this data. It is worth being said however that data that is almost completely unique however will cause this pendulum to swing in the other direction, causing worse compression in the worst case scenario since CSF has more overhead to organize the data than CSC. 

#### Positive Delta Endoding

We use this to take the indices inside of a fiber and encode the distance between them. While this doesn't cause us to store any less values, it can take larger values and make them smaller. Such as for a 10,000 x 10,000 matrix near the end of a column the indices could be [..., 9,973, 9,979, 9,981, 9,991], each of these values requires a 16 byte data type to store whereas if we positive delta encode them into [..., 3, 6, 2, 10] the values get much smaller and could potentially fit into a smaller data type. 

It should also be noted that this does make the data harder to traverse making it a tradeoff that isn't always worth it and will make data traversal slower, espeically if the data doesn't lend itself to the advantages of positive delta encoding.

#### Bytepacking

This is a process that takes all of the indices of a single fiber, finds the maximum value after positive delta encoding, and casts the indices to the smallest data type that doesn't lose precision. Such as if a user has a CSF matrix with indices stored in unsigned long long int yet no number exceedes 255. In this situation each fiber's indices would most likely be cast to a unsigned short int saving 7 bytes per index. This is great for isolating outlier data from enforcing a large data type and in combination with positive delta encoding can result in even very large matrices being heavily conmpressed with very little wasted space in the indices. 

As a side note, this as well makes the data somewhat more difficult to work with causing some degree of complication and slowdowns for data traversal but is often very much worth the savings. 

___

### CSF Compression Levels Explained

There are currently 3 compression levels to CSF.

*Compression Level 1: CSC Storage Format*

This is simply just a CSC matrix format. This is helpful for transitioning between deeper compression levels and back to a more workable format as many times CSC is far faster for certain algorithms. This also helps increase interoperability with other libraries and within CSF.

*Compression Level 2: CSF*

Level 2 is a derivative of CSC storage. The main difference is that the CSC is run length encoded by value and the number of times a value appears in a column is stored in a seperate vector. This results in a CSC format that instead is broken down by column into 3 vectors, the values, the indices, and the number of times each value appears. This is a very fast format to traverse and for sparse data the run length encoding helps compression ratios.

*Compression Level 3: CSF + Positive Delta Encoding + Bytepacking*

This is the compression level that will get the furthest compressed for most data, and very compressed for sparse redundant data. Each process squeezes out more and more bytes from the data and results in a very compressed matrix that doesn't have traversal speeds quite as fast as level 2. This level can be used if traversal speeds aren't as much of a factor or one is trying to use a dataset that would otherwise not fit in RAM without compression but still needs to be worked with.