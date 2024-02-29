# Lab description
In this lab, we will be working with the OpenMP code related to hyperspectral image compression. In this case, our focus will be on parallelization using DPC for a single hyperspectral block. Specifically, the practice will involve parallelizing the operations performed for compression (centroid calculation, centralization, calculation of the brightest pixel, spectral projection, and information subtraction).


DPC is a very new technology and for that reason the available documentation is not ver much. We recommend as text book reference [DPC Book](https://link.springer.com/content/pdf/10.1007%2F978-1-4842-5574-2.pdf). Before working on the code, it is very recommendable trying to visualize how the HyperLCA lossy hyperspectral compressor ([link](HLCA.md)).


filter works on a paper. 

As learning outcomes from the lab yo will:
1. Perform spectral transformations on hyperspectral images.
2. Parallelize code using DPC.
3. Analyze the performance improvement of the implementation.

# Important
Remember you should always compile with **icpx -fsycl**

# Task 1
[Link](src/task1)

# Task 2
[Link](src/task2)




