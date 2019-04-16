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
#include "classes/point.h"
#include "classes/segment.h"
#include "classes/flag.h"
using namespace std;

inline optional<vector<Segment>> sweep_line(vector<Flag> &flags, Color color) {
    vector<Segment> active;
    vector<Segment> broken_segments;

    const int bound_min = -1 << 20; // -2^10;
    const int bound_max = 1 << 20; // 2^10
    // add sentinels
    active.push_back(Segment(Point(bound_min, bound_min), Point(bound_max, bound_min), color));
    active.push_back(Segment(Point(bound_min, bound_max), Point(bound_max, bound_max), color));
    for (int i = 0; i < flags.size(); ++i) {
        Flag f = flags[i];
        if (f.type() == FlagType::start) {
            if (f.color() == color) {
                // flag has the same color as the segment color we are breaking. We check for intersection and flag on segment.
                for (int j = 0; j < active.size() - 1; ++j) {
                    if (orientation(active[j], f.p()) > 0 && orientation(active[j + 1], f.p()) < 0) {
                        if (intersects(active[j], f.s())) {
                            return {};
                        }
                        if (intersects(active[j+1], f.s()) ){
                            return {};         
                        }
                        active.insert(active.begin() + j + 1, f.s());   
                        break; 
                    } else if (orientation(active[j], f.p()) == 0) {
                        cout << "breaking" << endl;
                        // need to break the segment
                        Segment old_seg = Segment(active[j].p(), f.p(), color);
                        Segment new_seg = Segment(f.p(), active[j].q(), color);
                        broken_segments.push_back(old_seg); // old_seg will no longer be used. Push it to broken_segments.
                        active[j] = new_seg; // replace segment with new.
                        break;
                    }
                }
            } else {
                // flag has different color from the color we are breaking. 
                for (int j = 0; j < active.size() - 1; ++j) {
                    if (orientation(active[j], f.p()) == 0) {
                        cout << "breaking" << endl;
                        Segment old_seg = Segment(active[j].p(), f.p(), color);
                        Segment new_seg = Segment(f.p(), active[j].q(), color);
                        broken_segments.push_back(old_seg); // old_seg will no longer be used. Push it to broken_segments.
                        active[j] = new_seg; // replace segment with new.
                        break;
                    }
                }
            }
        } else {
            if (f.color() == color) {
                //cout << f << endl;
                for (int j = 0; j < active.size(); ++j) {
                    if (f.s() == active[j]) {
                    // TODO: We need to change f.s() == active[j] because active[j] might be a broken segment.
                        if (intersects(active[j - 1], active[j + 1])) {
                            return {};
                        }
                        broken_segments.push_back(active[j]);
                        active.erase(active.begin() + j);
                        break;
                    } 
                }
            }
        }
    }
    return broken_segments;
} 