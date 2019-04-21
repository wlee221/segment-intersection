#include <map>
#include <vector>
#include <iostream>
#include "../classes/point.hpp"
#include "../classes/segment.hpp"
#include "../classes/flag.hpp"
#include "../classes/above_below.hpp"

// helper function that inserts segment to a self-balancing tree.
inline void insert_segment(std::multimap<int, Segment> &active, const Segment s) {
    // inserts segment s with s.p().y() as its key value.
    active.insert({s.p().y(), s});
}

/******************************************************************
 * function get_above_below
 *
 * Input: 
 *      flags, vector of flags
 * Output: 
 *      map that maps each flag to an AboveBelow class
 *****************************************************************/
inline std::map<Flag, AboveBelow> get_above_below(std::vector<Flag> flags) {
    std::map<Flag, AboveBelow> above_below;
    std::multimap<int, Segment> active;

    const int bound_min = -1 << 20; // -2^10;
    const int bound_max = 1 << 20; // 2^10

    // add sentinels
    insert_segment(active, Segment(Point(bound_min, bound_min), Point(bound_max, bound_min), Color::red));
    insert_segment(active, Segment(Point(bound_min, bound_max), Point(bound_max, bound_max), Color::red));
    insert_segment(active, Segment(Point(bound_min, bound_min), Point(bound_max, bound_min), Color::blue));
    insert_segment(active, Segment(Point(bound_min, bound_max), Point(bound_max, bound_max), Color::blue));

    for (auto it = flags.begin(); it != flags.end(); ++it) {
        Flag f = *it;
        if (f.type() == FlagType::start) {
            auto upper_bound = active.upper_bound(f.p().y()); 
            Segment above = (*upper_bound).second;
            Segment below = (*prev(upper_bound)).second;
            insert_segment(active, f.s());

            Point flag_p = f.p();
            Color flag_color = f.color();

            // will find four segments below:
            Segment same_above;
            Segment same_below;
            Segment opposite_above;
            Segment opposite_below;

            // find segments above
            bool found_same = false, found_opposite = false; // flags identifying whether segment above of same and opposite color have been found.
            auto it_above = upper_bound; 
            while (!found_same || !found_opposite) {
                Point p = f.p(); // 
                Segment candidate = (*it_above).second;

                if (orientation(candidate, p) < 0) {
                    if (!found_same && candidate.type() == flag_color) {
                        found_same = true;
                        same_above = candidate;
                    } else if (!found_opposite && candidate.type() != flag_color) {
                        found_opposite = true;
                        opposite_above = candidate;
                    }
                }
                it_above = next(it_above);
            }

            // find segments below
            found_same = false;
            found_opposite = false; 
            auto it_below = prev(upper_bound); 
            while (!found_same || !found_opposite) {
                Point p = f.p(); // 
                Segment candidate = (*it_below).second;

                if (orientation(candidate, p) > 0) {
                    if (!found_same && candidate.type() == flag_color) {
                        found_same = true;
                        same_below = candidate;
                    } else if (!found_opposite && candidate.type() != flag_color) {
                        found_opposite = true;
                        opposite_below = candidate;
                    }
                }
                it_below = prev(it_below);
            }

            AboveBelow ab = AboveBelow(same_above, same_below, opposite_above, opposite_below);
            above_below[f] = ab;
        } else {
            //cout << f << endl;
            int key = f.s().p().y(); // get the left endpoint, which was used as a key when the start flag was added.
            auto key_range = active.equal_range(key); // there might be multiple segments at key, so get a range of elements.
            auto to_remove = std::find(key_range.first, key_range.second, std::pair<const int, Segment> (key, f.s()));

            Segment s = (*to_remove).second;
            Segment below = (*prev(to_remove)).second;
            Segment above = (*next(to_remove)).second;
            active.erase(to_remove);
            
            Point flag_p = f.p();
            Color flag_color = f.color();

            Segment same_above = f.s(); 
            Segment same_below = f.s();
            // need to find two segments below:
            Segment opposite_above;
            Segment opposite_below;

            // find opposite segment above
            auto it_above = active.upper_bound(f.p().y()); 
            while (true) {
                Point p = f.p(); // 
                Segment candidate = (*it_above).second;

                if (orientation(candidate, p) < 0 && candidate.type() != flag_color) {
                    opposite_above = candidate;
                    break;
                }
                it_above = next(it_above);
            }

            // find opposite segment below
            auto it_below = prev(active.upper_bound(f.p().y())); 
            while (true) {
                Point p = f.p(); // 
                Segment candidate = (*it_below).second;

                if (orientation(candidate, p) > 0 && candidate.type() != flag_color) {
                    opposite_below = candidate;
                    break;
                }
                it_below = prev(it_below);
            }
            AboveBelow ab = AboveBelow(same_above, same_below, opposite_above, opposite_below);
            above_below[f] = ab;            
        }
    }
    return above_below;
}