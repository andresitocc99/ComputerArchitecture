# Task 1
In this task, you will parallelize part of the code using DPC. Specifically, you will need to translate the centroid operation to DPC.

## 0. Prepare the code
First, locate the code corresponding to the centroid and how the hyperspectral cube is read from the image hosted on [mega](https://mega.nz/file/Z5JUkSoI#boptGx0TD4YU1FGz5WxVkxgB0-fav1sQiVVCk2lz_CA). Remember that this time we will only use one block, so you need to modify the amount of data to be read.

## 1. Create the queue using a default device selector
Find out how to create the queue and pass the default device selector as a parameter to the queue. Remember that the queue has to be created before any computation.
    ```
    sycl::queue q(sycl::default_selector_v);
    ```

## 2. What is the queue used for?
It is used to run my kernels. By running the queue at the start of the program, I guarantee that all tasks submitted to this queue will be run on the selected device.

## 3. Create the corresponding buffer for each array
Remember that one of the ways to access memory in DPC is through buffers and accessors. This is the method we will use in this practice. To do this, create the buffers once the memory spaces where we will work are initialized, i.e., just before the for loop.
    ```
    void averagePixel(sycl::queue &q,unsigned short *ImgRef, int *centroid) {
  
        sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
        sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));

    }     
    ```


## 4. Create a range for the kernel
The first parameter of the *parallel_for* will be the workspace range. To define this range, we have to indicate, at compile time, the number of dimensions it has and the size of each dimension.

    ```
    void averagePixel(sycl::queue &q,unsigned short *ImgRef, int *centroid) {
  
        sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
        sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));

        sycl::range<1> workRange(BANDS);
    }
    ```


## 5. Submit a task to the queue
Now we will create the job inside the queue where, in the following tasks, we will insert the code to: request access to variables and execute the job. Find out how to create the job for the queue. Verify that the code compiles.

    ```
    void averagePixel(sycl::queue &q,unsigned short *ImgRef, int *centroid) {
  
        sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
        sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));

        sycl::range<1> workRange(BANDS);

        q.submit([&](sycl::handler& h) {
            
        }).wait(); 
    }
    ```


## 6. Request access to buffers
Remember that we have created buffers to abstract access to different variables. As seen in theory, you have to request access to each buffer through accessors. **In the first lines within the queue**, define the accessors that we need.
    ```
    void averagePixel(queue &q,unsigned short *ImgRef, int *centroid) {
  
        sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
        sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));
        sycl::range<1> workRange(BANDS);

        q.submit([&](sycl::handler& h) {

            auto imgAcc = imgRefBuf.get_access<sycl::access::mode::read>(h);
            auto centroidAcc = centroidBuf.get_access<sycl::access::mode::discard_write>(h);

        }).wait(); 
    }
    ```


Clues:
* Choose the right permissions.

## 7. Create the parallel_for
Now that we have access to each buffer, we need to request, through the handler, the parallel_for indicating: the kernel's range (review the previous steps) and the kernel itself. Initially, leave the kernel empty and check that the compilation is correct.

Once the parallel_for is completed (remember to add the centroid calculation code in the kernel), compile the code and make sure there are no compilation errors.

    ```
    void averagePixel(queue &q,unsigned short *ImgRef, int *centroid) {
  
        sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
        sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));
        sycl::range<1> workRange(BANDS);
        // Sending task to the queue for it execution in the device
        q.submit([&](sycl::handler& h) {
            // Accessing to the buffers
            auto imgAcc = imgRefBuf.get_access<sycl::access::mode::read>(h);
            auto centroidAcc = centroidBuf.get_access<sycl::access::mode::discard_write>(h);

            h.parallel_for(workRange, [=](sycl::id<1> bandId) {
                int sum = 0;
                for(int pixel = 0; pixel < BLOCK_SIZE; ++pixel) {
                    int index = pixel * BANDS + bandId[0];
                    sum += imgAcc[index];
                }
                centroidAcc[bandId] = sum / BLOCK_SIZE;
            });

        }); 
    }
    ```

Clues:
* Look in the reference code. Most likely, you will need to adapt the reference code to the structure followed by DPC.

## 8. Wait for the task and get the results
Finally, all that's left is to wait for the queue. Find out how to wait and access the kernel's output buffer using a host_accessor. By creating the host_accessor to the buffer, the runtime ensures that you have access to it, and you can access it as you normally would.
    ```
    void averagePixel(sycl::queue &q,unsigned short *ImgRef, int *centroid) {
  
        sycl::buffer<unsigned short, 1> imgRefBuf(ImgRef, sycl::range<1>(BLOCK_SIZE * BANDS));
        sycl::buffer<int, 1> centroidBuf(centroid, sycl::range<1>(BANDS));
        sycl::range<1> workRange(BANDS);
        // Sending task to the queue for it execution in the device
        q.submit([&](sycl::handler& h) {
            // Accessing to the buffers
            auto imgAcc = imgRefBuf.get_access<sycl::access::mode::read>(h);
            auto centroidAcc = centroidBuf.get_access<sycl::access::mode::discard_write>(h);

            h.parallel_for(workRange, [=](sycl::id<1> bandId) {
                int sum = 0;
                for(int pixel = 0; pixel < BLOCK_SIZE; ++pixel) {
                    int index = pixel * BANDS + bandId[0];
                    sum += imgAcc[index];
                }
                centroidAcc[bandId] = sum / BLOCK_SIZE;
            });

        }); 
        q.wait();

        sycl::host_accessor readCentroid(centroidBuf, sycl::read_only);
        for (int i = 0; i < BANDS; ++i) {
            centroid[i] = readCentroid[i];
        }
    }
    ```


**Verify that the code produces the same results as the sequential code**
**Save the final code in results/task1/dpcHLCA.cpp**
