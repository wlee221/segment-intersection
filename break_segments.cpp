/*
 * SI5: Breaks red segments such that none contains any flag point. 
 * Note that sweep_line is written generalized such that it can break red OR 
 * blue segments. This is to help implement SI6, where I need to break both colors.
 *
 * Author:  William Lee
 * Class:   Comp 651
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <optional>
#include <chrono> 
#include "classes/point.h"
#include "classes/segment.h"
#include "classes/flag.h"
using namespace std;

optional<vector<Segment>> sweep_line(vector<Flag> &flags, Color c);

int main(int argc, char* argv[]) {
    if (argc != 3) 
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;

    // read input:
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    vector<Flag> flags;

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k;
        int px, py, rx, ry;

        input >> m >> n >> k;

        for (int i = 0; i < m + n; i++) {
            input >> px >> py >> rx >> ry;
            Segment s;
            if (i < m) {
                s = Segment(Point(px, py), Point(rx, ry), Color::red);
            } else {
                s = Segment(Point(px, py), Point(rx, ry), Color::blue);
            }
            flags.push_back(Flag(s, s.p(), FlagType::start));
            flags.push_back(Flag(s, s.q(), FlagType::terminal));
        }

        sort(flags.begin(), flags.end());

        auto start = chrono::high_resolution_clock::now(); 

        optional<vector<Segment>> broken_segments;
        for (int i = 0; i < num_execution; ++i) {
            broken_segments = sweep_line(flags, Color::red);
        }

        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration<float>(stop - start);

        std::vector<Segment> red;
        if (broken_segments.has_value()) {  
            red = broken_segments.value();
            for (const auto &s: red) {
                cout << s << endl;
            }
        } else {
            cerr << "Error: Intersection detected." << endl;
        }

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;
    } else {
        cerr << "File could not be opened." << endl;
    }
    return 0;
}

optional<vector<Segment>> sweep_line(vector<Flag> &flags, Color color) {
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
                        cout << "breaking";
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
                        cout << "breaking";
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