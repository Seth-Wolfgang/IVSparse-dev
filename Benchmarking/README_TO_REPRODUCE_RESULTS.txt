
Most plots listed in the publication related to this paper can be recreated by running 

runFullSimulatedBench.sh which is located in: Benchmarking/lib/runFullSimulatedBench.sh
The second plot listed in regards to memory usage uses a different script. To recreate the plot where redundancy is fixed, 
you may simply compile and run densityBenchmark.cpp which is located in: Benchmarking/lib/densityBenchmark.cpp. The parameters used
for the publication should be set by default. 

Results for benchmarks are stored in /Benchmarking/results, their redundancies or densities are listed in the file name.

Results may vary due to differences in hardware, but compression sizes will remain the same.
To create plots, we used the R language to create plots generated from data produced by running runFullSimulatedBench.sh.

The .Rmd file to produce plots is in /Benchmarking/R/simulated_bench_visualization.Rmd

Simply run all chunks in the .Rmd file to produce the plots. If an error occurs, please check that the paths to the data files are correct.
Some libraries may need to be installed. If you are unfamiliar with R, see lines including library() to see what you need to install.

Default paramters for simulated benchmarks:
ROWS = 10000
COLS = 100

For runFullSimulatedBench.sh,

*   #define NUM_ITERATIONS 10
*   #define DENSITY 0.01 -> THIS WILL CHANGE IF YOU RUN WITH runFullSimulatedBench.sh. This is intentional.
*   #define MATRICES 1000
*   #define VALUE_TYPE double
    
For densityBenchmark.cpp,

 *  #define NUM_ITERATIONS = 10
 *  #define REDUNDANCY = 0.1 -> this is actually 1 - REDUNDANCY, so it is 90% redundant
 *  #define MATRICES 1000
 *  #define VALUE_TYPE double

## Real Data -> see Table 1 in publication

To run the real data benchmarks, you will need to download the data from the following link: 

Web of Science: https://paperswithcode.com/dataset/web-of-science-dataset
    - Note: This data was run through a count vectorizer, the script is provided in helpful_scripts/
            and later CSC_to_COO.py was used to convert the data to COO format.
MovieLens: https://grouplens.org/datasets/movielens/
    - Note: We used the ratings.csv file, as part of their 25 million data set. Some finangling may be required to
            get the data to run properly in /lib/datasetSizeBench.cpp

Single-cell: https://www.10xgenomics.com/resources/datasets/aggregate-of-900k-human-non-small-cell-lung-cancer-and-normal-adjacent-cells-multiplexed-samples-16-probe-barcodes-1-standard
    - Note: this one is a matrix market file and source code should be provided. 
            It is rather large (20gb). We used filtered_feature_bc_matrix.mtx and 
            used nearly 40gb of ram on my machine.

PR02R: https://www.cise.ufl.edu/research/sparse/matrices/Fluorem/PR02R.html
    - Note: this may be found on either the official SuiteSparse website or the University of Florida site.
            We used the .mtx file.

Sim Unique/Binary:
    - Note: These were generated matrices. The dimensions and density are listed on Table 1, the only 
            difference is all values in Sim Binary were 1, and all values in Sim Unique had values generated
            with rand() and allowed for values between 1 and INT64_MAX

All data here was run through datasetSizeBench.cpp, which is located in Benchmarking/lib/datasetSizeBench.cpp.
Some value templates may need to be changed depending on the data you are using. The lines have comments next to them
to indicate what may need to be changed. The program will segfault if something is off. 
Some code may need to be commented/uncommented depending on the dataset you are trying to reproduce results for.


runBenchmark.sh is not used in the publication, but allows for benchmarkings using matrices from SuiteSparse Matrix Collection.
Early benchmarks used this, but we found the prevalence of diagonal matrices in the collection to be problematic for our data structure. 
IVSparse is not meant to be used for diagonal matrices, and so we do not include these results in our benchmarks. We did not create ssget, but 
a ours is a modifed version to store matrices in /Benchmarking/matrices. A link to the original repo/creator is provided at the top of the file.