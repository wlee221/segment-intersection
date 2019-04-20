#include <vector>
#include <algorithm>
#include "../classes/flag.hpp"

/******************************************
 * function sort_flags
 *
 * Input: 
 *      flags, vector of flags
 * Output: 
 *      sorts given vector (no return value)
 *****************************************/
inline void sort_flags(std::vector<Flag> &flags) {
    std::sort(flags.begin(), flags.end());
}

