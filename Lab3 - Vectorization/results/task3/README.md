# Task 3: Vectorization

## Questions

### 1. Before starting the vectorization process, it is crucial to understand the specifics of your machine. What are the SIMD multimedia extensions available on your architecture?

That's the command i've used to obtain all available media SIMD extensions in my architecture:
```bash
cat /proc/cpuinfo | grep flags
```

### 2. Review the analysis you've conducted on the complexmul.cpp program. Intel Advisor should have identified an underutilization of instructions, directly related to vectorization, as it indicates that you have available SIMD extensions that are not being leveraged. To vectorize the algorithm, Intel Advisor itself provides guidance on how to proceed. What steps have you taken to vectorize the loop? Keep in mind that you should pursue maximum vectorization that your architecture permits.

I've compiled the file 'complexmul.cpp' with the highest ISA available in my computer.
```bash
icpc -g -qopenmp -xCORE-AVX2 -o complexmul complexmul.cpp
```

### 3. After vectorizing the program, conduct an analysis and save it under the name "task3":

#### 3.1. What is the value indicated in the 'Vector Length' field? Considering the extensions you're utilizing and the program's use of 32-bit floats, is this the expected value? Justify the anticipated value, whether the actual value aligns with your expectations or not.

   * Vector Length: 16

#### 3.2. What was the extent of the improvement? Discuss whether this is the outcome you predicted; if not, explain what you believe might be the reason (Hint: Intel Advisor can offer insights into what the issue might be).
   * Gain: 7.07x
