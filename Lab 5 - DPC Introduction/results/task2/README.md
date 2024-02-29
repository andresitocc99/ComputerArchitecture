# Task 2
Code in src/task2/buffer.cpp should represent the following flow:
1. Initialize buffer A
2. Add to each item in A the index of the iteration
3. Initialize buffer B the same way than A
4. Compute B as the result of B multiplied by A

## 1. Check the result and show it below
Compiling it with command:
```
dpcpp -o buffer buffer.cpp
```

Output in console:
```
0
2
8
18
32
50
72
98
128
162
200
242
288
338
392
450
```

## 2. Which abstraction is being used for data containers?
We use Buffers.

## 3. How is the DAG being built implicitly or explicitly?
It's built implicitly, because its not specified any order to execute the buffers, so that buffers are executed sequentally

## 4. Enumerate all dependencies and their types

Type of dependencies: Read After Write (RAW), Write After Write (WAW) and Write after Read (WAR)

- WAW: Between Kernel 1 and Kernel 2 on buffer A.
- WAW: Between Kernel 3 and Kernel 4 on buffer B.
- RAW: Between Kernel 2 and Kernel 4 on buffer A.