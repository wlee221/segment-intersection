#include <map>
#include <optional>
#include "../classes/point.hpp"
#include "../classes/segment.hpp"
#include "../classes/flag.hpp"

// helper function that inserts segment to a self-balancing tree.
inline void insert_segment(std::multimap<int, Segment> &active, const Segment s) {
    // inserts segment s with s.p().y() as its key value.
    active.insert({s.p().y(), s});
}

/******************************************************************
 * function sweep_line
 *
 * Input: 
 *      flags, vector of flags  
 * Output: 
 *      If there exists crossing, return intersecting segment pair. 
 *      Otherwise, return empty pair {}.
 *****************************************************************/
inline std::optional<std::pair<Segment, Segment>> sweep_line(std::vector<Flag> &flags) {
    std::multimap<int, Segment> active;  

    const int bound_min = -1 << 20; // -2^10;
    const int bound_max = 1 << 20; // 2^10
    // add sentinels
    Segment top_sentinel = Segment(Point(bound_min, bound_min), Point(bound_max, bound_min), Color::red);
    Segment bot_sentinel = Segment(Point(bound_min, bound_max), Point(bound_max, bound_max), Color::red);
    insert_segment(active, top_sentinel);
    insert_segment(active, bot_sentinel);

    for (auto it = flags.begin(); it != flags.end(); ++it) {
        Flag f = *it;
        if (f.type() == FlagType::start) {
            // upper_bound points to an segment above the flag 
            auto upper_bound = active.upper_bound(f.p().y()); 
            Segment above = (*upper_bound).second;
            Segment below = (*prev(upper_bound)).second;
            if (intersects(above, f.s()))
                return std::make_pair(above, f.s());
            if (intersects(below, f.s()))
                return std::make_pair(below, f.s());
            insert_segment(active, f.s());
        } else {
            // need to remove the segment of f. 
            int key = f.s().p().y(); // get the left endpoint, which was used as a key when the start flag was added.
            auto key_range = active.equal_range(key); // there might be multiple segments at key, so get a range of elements.
            auto to_remove = std::find(key_range.first, key_range.second, std::pair<const int, Segment> (key, f.s()));

            Segment s = (*to_remove).second;
            Segment below = (*prev(to_remove)).second;
            Segment above = (*next(to_remove)).second;
            if (intersects(below, above)) 
                return std::make_pair(below, above);
            active.erase(to_remove);

        }
    }
    return {};
} 