# Algorithm Implementations
See below for algorithm details. Note that N = m + n, ie. number of segments. 

### SI1: brute_force 
*Input*: `red`, `std::vector` of red segments. `blue`, `std::vector` of blue segments  
*Output*: number of red/blue intersections.  

### SI3: sort_flags 
*Input*: `flags`, `std::vector` of flags    
*Output*: sorts `flags` (no return value)   

### SI4: vertify_red 
*Input*: `flags`, `std::vector` of flags  
*Output*: intersecting segment pair if it exists. Otherwise, return empty pair {}.   

### SI5: break_segments
*Input*: `flags`, `std::vector` of flags. `color`, color of the segments to break.  
*Output*: `std::vector` of segments with specified color, broken such that none contains flag point.    

### SI6: get_above_below
*Input*: `flags`, `std::vector` of flags. `color`, color of the segments to break.  
*Output*: `std::map` that maps each flag to an AboveBelow class   
