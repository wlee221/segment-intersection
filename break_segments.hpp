/*
 * Implementation of break_segments(...). To be used in SI5 and onwards. 
 *
 * Author: William Lee
 * Class: Comp 651
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <optional>
#include <map>
#include "classes/point.hpp"
#include "classes/segment.hpp"
#include "classes/flag.hpp"
using namespace std;

inline void insert_segment(multimap<int, Segment> &active, const Segment s) {
    // inserts segment s with s.p().y() as its key value.
    active.insert({s.p().y(), s});
}

inline optional<vector<Segment>> sweep_line(vector<Flag> &flags, Color color) {
    multimap<int, Segment> active;
    vector<Segment> broken_segments;

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
            auto upper_bound = active.upper_bound(f.p().y()); 
            Segment above = (*upper_bound).second;
            Segment below = (*prev(upper_bound)).second;

            if (f.color() == color) {
                // f.p() might be on "below". Break "below" if so. /
                if (orientation(below, f.p()) == 0) {
                    cout << "breaking" << endl; // TODO: Remove this
                    Segment old_seg = Segment(below.p(), f.p(), color);
                    Segment new_seg = Segment(f.p(), below.q(), color);
                    broken_segments.push_back(old_seg); // old_seg will no longer be used. Push it to broken_segments.

                    active.erase(prev(upper_bound)); 
                    insert_segment(active, new_seg); // replace segment with new.    
                }
                if (intersects(above, f.s()))
                    return {};
                if (intersects(below, f.s())) // Note: this is trivially false if f.p() was on below.
                    return {};
                insert_segment(active, f.s());
            } else {
                if (orientation(below, f.p()) == 0) {
                    cout << "breaking" << endl; // TODO: Remove this
                    Segment old_seg = Segment(below.p(), f.p(), color);
                    Segment new_seg = Segment(f.p(), below.q(), color);
                    broken_segments.push_back(old_seg); // old_seg will no longer be used. Push it to broken_segments.

                    active.erase(prev(upper_bound)); 
                    insert_segment(active, new_seg); // replace segment with new.    
                }
            }
        } else {
            if (f.color() == color) {
                //cout << f << endl;
                int key = f.s().p().y(); // get the left endpoint, which was used as a key when the start flag was added.
                auto key_range = active.equal_range(key); // there might be multiple segments at key, so get a range of elements.
                auto to_remove = std::find(key_range.first, key_range.second, pair<const int, Segment> (key, f.s()));
                if (to_remove == active.end()) 
                    cerr << "ERROR: Could not find segment to remove" << endl;

                Segment s = (*to_remove).second;
                Segment below = (*prev(to_remove)).second;
                Segment above = (*next(to_remove)).second;
                if (intersects(below, above)) 
                    return {};
                broken_segments.push_back(s);
                active.erase(to_remove);
            }
        }
    }
    return broken_segments;
}