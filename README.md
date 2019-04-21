# Segment Intersection
**Author**: William Lee  
**Class**: Comp 651

## Introduction
This repository contains stages for red/blue segment intersections as outlined in [staged programming project](https://raindrops.in/snoeyink/view/54084b864251df7f2f8b4567). 

### Structure
This repository is divided into following directories:

* `segment-intersection/`: contains C++ source files to compile. 
* `segment-intersection/classes`: contains class header files.
    * orientations tests involving geometric primitives are implemented here.
    * common operators are overloaded here for concise code in main files.
* `segment-intersection/impl`: contains algorithm implementations. 
* `segment-intersection/test_data`: contains test data in txt format (provided by Prof. Snoeyink) . 
    * Note that `redblue_2000.txt` contains red/red intersections.

### Compilation and Execution
##### Compilation
C++17 Compiler is required to compile the source files. For most commercial compilers, you need to add `-std=c++17` flag.  
  
Bash program `compile.sh` is provided to compile all source files with gcc/g++.

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
* First line is three numbers `m n k`.
* `m` rows of coordinates `px py rx ry` of red segments.
* `n` rows of coordinates `px py rx ry` of blue segments.

### Source file description
*Note*: See README.md in `impl/` to see algorithm input, output, and complexity details. 

##### SI1: brute_force
`brute_force.cpp` reads the test file and counts the number of red/blue intersection and checks if it matches `k`. It checks every pair of red and blue segments and checks for intersection. If the number of intersection matches `k`, then program outputs `VERIFIED`. Otherwise, it outputs the number of computed intersections. 

##### SI3: sort_flags 
`sort_flags.cpp` reads `test file` and generates start and terminal flags for each segment. Then, it sorts the flags using `std::sort` and prints to the output stream. Sorting is based on three-way comparison function in `classes/flag.hpp`. 

##### SI4: vertify_red
`verify_red.cpp` reads red segments from `test_file` and uses Bentley-Ottoman sweep to check that there exists no red/red crossings. To keep track of active segments, we use `std::multimap` for O(log n) operations (Note that most compilers uses rb-tree to implement `std::multimap`). Program outputs `VERIFIED` if there exists no crossings. Otherwise, it prints the crossing segment pairs.

##### SI5: break_segments
`break_segments.cpp` reads segments from `test_file` and breaks the red segments such that no segments share any interior points and contain no flag points in their interior. Its algorithm is an extension from Bentley-Ottoman sweep used in SI4 with additional end point checks.

##### SI6: get_above_below
`get_above_below.cpp` reads (broken) segments from `test_file` and maps each flag to `AboveBelow` class containing red and blue segments above and below.

## Results
Table below summarized average runtime for each program. Runtimes were measured using `test_data/redblue_200.txt` and were averaged over 1000 runs.

|     Program     | Runtime (microseconds) |
|:---------------:|:----------------------:|
|   brute_force   |         1099.45        |
|    sort_flags   |         165.307        |
|    verify_red   |         143.354        |
|  break_segments |         180.569        |
| get_above_below |         1002.94        |

## Conclusion
##### Accomplished

##### Unaccomplished

##### Reflection