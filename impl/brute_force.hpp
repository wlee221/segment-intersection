#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../classes/point.hpp"
#include "../classes/segment.hpp"

/******************************************
 * function count_intersections
 *
 * Input: 
 *      red, vector of red segments 
 *      blue, vector of red segments    
 * Output: 
 *      number of red/blue intersections
 *****************************************/

inline int count_intersections(std::vector<Segment> &red, std::vector<Segment> &blue) {
    int k = 0; // # red/blue intersections
    for (const auto &red_seg : red) 
        for (const auto &blue_seg : blue) 
            if (intersects(red_seg, blue_seg)) 
                ++k;
    return k;
}