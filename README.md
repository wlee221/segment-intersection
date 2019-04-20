# Segment Intersection
##### Author: William Lee

## Introduction
This repository contains stages for red/blue segment intersections as outlined in [staged programming project](https://raindrops.in/snoeyink/view/54084b864251df7f2f8b4567). 

### Structure
This repository is divided to following directories:

* `segment-intersection/`: contains C++ source files to compile. 
* `segment-intersection/classes`: contains class header files.
* `segment-intersection/impl`: contains algorithm implementation header files. 
* `segment-intersection/test_data`: contains test data in txt format (provided by Prof. Snoeyink) . 
    * Note that `redblue_2000.txt` contains red/red intersections.

### Compilation and Execution
##### Compilation
C++17 Compiler is required to compile the source files. For most commercial compilers, you need to add `-std=c++17` flag to enable c++17 features. Note that no external libraries are required.  
Bash program `compile.sh` is provided to help compilation with gcc/g++. It compiles all .cpp source files and saves executables in `build/`. 

##### Execution 
Executables take two arguments: 
* `file_path`: location of the test file.
* `num_executables`: number of times to run the algorithm. 
Given the arguments, program reads `file_path` and outputs average execution time.

##### Example
For example, to compile and run `brute_force.cpp` on test file `redblue_200.txt` with `num_execution = 100`:
```
g++ brute_force.cpp -std=17 -o BFwilliam
./BFwilliam test_data/redblue_200.txt 100
```
