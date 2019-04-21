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
g++ brute_force.cpp -std=c++17 -o BFwilliam
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

## Reflection
I finished SI1 through SI6, but could not finish SI7 by deadline. Following summarizes my reflection on this project.

##### SI1 through 6
Because I could not finish SI7 in time, I focused most of time on improving SI6 through SI7, with degeneracies handled. Major improvement was on implementing efficient data structure for sweep lines. Although c++ library does not support self balancing bst, I learned that most commercial compilers uses rb-tree to implement `std::multimap<Key, Value>`. Multimap is an ordered map that allows duplicate key. This fit really well into the project because I could use y-values for `Key` and `Flag` for `Value` that allows O(log n) insertions, deletions, and search. The code is also cleaner than using linear search with vectors (see the commit [here](https://github.com/wlee221/segment-intersection/commit/f8c7129ba4d637267dead2989a9afba9e832198d).  
I also focused on improving code conciseness. In particular, I used `std::optional` to report intersecting red/red segments, which manages an optional contained value. This is enables concise error handling, because I only need to add value if and only if there exists a crossing.
##### Challenges and lessons
*SI1 through 6:* 
* Keeping concise code. This project involved multiple geometric primitives that I built from scratch. Hence, my code was initially unorganized. The following approaches helped:
    * Data structure: I implemented data structure with arrays. This is resulted in multiple linear search and overall unreadable code. I was surprised that using a rb-tree was actually much more readable although it involves more advanced operations.  
    * Refractoring and operation overloading were especially helpful. As I moved classes and algorithm implementation to subdirectories, the source files became more shorter (all within 100 lines).  
    
*SI7*
* Despite understanding algorithm for SI7, I could not finish it by the deadline. In particular, writing custom data structures for the bundles took more time than expected. This resulted from inappropriate time management and workflow:
    *  I used arrays to implement SI4-7 initially. When I switched to rb-tree, I had to refractor all sweep line codes, when I already spent so much time on implementing it with arrays. Instead, I should have started with rb-tree, or refractor after I finished SI7. 

##### Improvements
* Implement SI7 
* Use Cmake to compile the programs so that programs can be compiled in multiple architectures. 
* Better error handling (exit program on detection)
* get_above_below seems especially slow, so work on improving it.
* Unit testing
* More test cases
