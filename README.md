# Wolfgang Compression, The Third of its name, Lord of the Andels, Ruler of the First Men
> "Most anyone would assert that this idea defies the laws of science.  But try it." -DeBruine, 2022 \
> "Now this, this is pod racing" -Skyler, 2022

# SRLE
> "Most anyone would assert that this idea defies the laws of science.  But try it." -DeBruine 2022

# Issues because I forgot and had to remember after winter break:
* Eigen vector has 0's in it
Issue could be caused by things being casted to int.
* Eigen vector is not being properly converted to SRLE -> But its close! Test case did show its working, but random case does NOT

* Optimize Optimize Optimize

* Turn iterator into a subclass of the constructor

# Personal issues for Seth
* Please use more memorable variable names for easy readability.

# Optional:
* Write actual tests! Secondary effect -> make Dr. Fredericks proud


Good news: We're close and I can see the light at the end of the tunnel :)


meeting notes 1/10

* total data needed for constructor

> num of values x valuetype + num of columns x coltype + num of indices x index type
* Read pointers backwards
> later job
* Throw in a pointer to the iterator to make it work
> also later job
* Change how we positive delta encode
> pointer - 1 instead of using casts and a temporary
* Use floor() and log_2 to instead of switch statement to find size of values
> Switch statement is fine, this could be faster.
*

