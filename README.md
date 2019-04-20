# Segment Intersection
##### Author: William Lee
##### Class: Comp 651

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
C++17 Compiler is required to compile the source files. For most commercial compilers, you need to add `-std=c++17` flag to enable c++17 features.  
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
## Project Description
### Input text file format
* First line is three numbers `m n k`
* m rows of coordinates `px py rx ry` of red segments
* n rows of coordinates `px py rx ry` of blue segments

### `/brute_force.cpp` (SI1)
**Algorithm used**: `count_intersections` in `impl/brute_force.hpp`  
**Input**: `red`, `std::vector` of red segments. `blue`, `std::vector` of blue segments  
**Output**: number of red/blue intersections.  
**Runtime Complexity**: `O(N<sup>2</sup>)`, where `N = m + n`.  
  
`brute_force.cpp` reads the test file and counts the number of red/blue intersection and checks if it matches `k`. It checks every pair of red and blue segments and checks for intersection. Segment intersection test is performed using four orientation tests. If the number of intersection matches `k`, then program outputs `VERIFIED`. Otherwise, it outputs the number of computed intersections. 

### `/sort_flags.cpp` (SI3)
**Algorithm used**: `sort_flags` in `impl/sort_flags.hpp`  
**Input**: `flags`, `std::vector` of flags    
**Output**: sorts `flags` (no return value) 
**Runtime Complexity**: `O(Nlog N)`, where `N = m + n`.  

`sort_flags.cpp` first reads `test file` and generates start and terminal flags for each segment. It then sorts the flags using `std::sort` and prints to the output stream. Sorting is based on three-way comparison function in `classes/flag.hpp`. 