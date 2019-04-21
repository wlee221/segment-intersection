# Algorithm Implementations

### SI1: brute_force
**Algorithm Details**:  
    &nbsp;&nbsp;&nbsp;&nbsp;*Input*: `red`, `std::vector` of red segments. `blue`, `std::vector` of blue segments  
    &nbsp;&nbsp;&nbsp;&nbsp;*Output*: number of red/blue intersections.  
    &nbsp;&nbsp;&nbsp;&nbsp;*Runtime Complexity*: O(N<sup>2</sup>), where N = m + n.  

### SI3: sort_flags 
**Algorithm Details:**  
    &nbsp;&nbsp;&nbsp;&nbsp;*Input*: `flags`, `std::vector` of flags    
    &nbsp;&nbsp;&nbsp;&nbsp;*Output*: sorts `flags` (no return value)   
    &nbsp;&nbsp;&nbsp;&nbsp;*Runtime Complexity*: O(Nlog N), where N = m + n.  

### SI4: vertify_red
**Algorithm Details**:   
    &nbsp;&nbsp;&nbsp;&nbsp;*Input*: `flags`, `std::vector` of flags  
    &nbsp;&nbsp;&nbsp;&nbsp;*Output*: intersecting segment pair if it exists. Otherwise, return empty pair {}.   
    &nbsp;&nbsp;&nbsp;&nbsp;*Runtime Complexity*: O(Nlog N), where N = m + n.  

### SI5: break_segments
**Algorithm Details**:   
    &nbsp;&nbsp;&nbsp;&nbsp;*Input*: `flags`, `std::vector` of flags. `color`, color of the segments to break.  
    &nbsp;&nbsp;&nbsp;&nbsp;*Output*: `std::vector` of segments with specified color, broken such that none contains flag point.    
    &nbsp;&nbsp;&nbsp;&nbsp;*Runtime Complexity*: O(Nlog N), where N = m + n.  

### SI6: get_above_below
**Algorithm Details**:   
    &nbsp;&nbsp;&nbsp;&nbsp;*Input*: `flags`, `std::vector` of flags. `color`, color of the segments to break.  
    &nbsp;&nbsp;&nbsp;&nbsp;*Output*: `std::map` that maps each flag to an AboveBelow class   
    &nbsp;&nbsp;&nbsp;&nbsp;*Runtime Complexity*: O(Nlog N), where N = m + n.  