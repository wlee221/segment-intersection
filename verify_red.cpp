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

optional<pair<Segment, Segment>> sweep_line(vector<Segment> &red, vector<Flag> &flags);

int main(int argc, char* argv[]) {
    if (argc != 3) 
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;

    // read input:
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    vector<Segment> red;
    vector<Flag> flags;

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k;
        int px, py, rx, ry;

        input >> m >> n >> k;

        for (int i = 0; i < m; i++) {
            input >> px >> py >> rx >> ry;
            Segment s = Segment(Point(px, py), Point(rx, ry), Color::red);
            red.push_back(s);
            flags.push_back(Flag(s, s.p(), FlagType::start));
            flags.push_back(Flag(s, s.q(), FlagType::terminal));
        }

        sort(flags.begin(), flags.end());
        auto start = chrono::high_resolution_clock::now(); 

        for (int i = 0; i < num_execution; ++i) {
            sweep_line(red, flags);
        }

        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration<float>(stop - start);

        auto intersection = sweep_line(red, flags);
        if (intersection.has_value()) {
            cerr << "ERROR: intersection was found: " << intersection.value().first
                 << ", " << intersection.value().second << "." << endl;
        } else {
            cout << "VERIFIED" << endl;
        }

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;
    } else {
        cerr << "File could not be opened." << endl;
    }
    return 0;
}

optional<pair<Segment, Segment>> sweep_line(vector<Segment> &red, vector<Flag> &flags) {
    vector<Segment> active;

    const int bound_min = -1 << 20; // -2^10;
    const int bound_max = 1 << 20; // 2^10
    // add sentinels
    active.push_back(Segment(Point(bound_min, bound_min), Point(bound_max, bound_min), Color::red));
    active.push_back(Segment(Point(bound_min, bound_max), Point(bound_max, bound_max), Color::red));

    // TODO: use self balancing BST to implement this.
    for (int i = 0; i < flags.size(); ++i) {
        Flag f = flags[i];
        if (f.type() == FlagType::start) {
            for (int j = 0; j < active.size() - 1; ++j) {
                if (active[j].point_orientation(f.p()) > 0 && active[j + 1].point_orientation(f.p()) < 0) {
                    if (intersects(active[j], f.s())) {
                        return pair<Segment, Segment> (active[j], f.s());
                    }
                    if (intersects(active[j+1], f.s()) ){
                        return pair<Segment, Segment> (active[j], f.s());                    
                    }
                    active.insert(active.begin() + j + 1, f.s());
                    break;
                } 
            }
        } else {
            for (int j = 0; j < active.size(); ++j) 
                if (f.s() == active[j]) {
                    if (intersects(active[j - 1], active[j + 1])){
                        return pair<Segment, Segment> (active[j - 1], active[j + 1]);
                    }
                    active.erase(active.begin() + j);
                    break;
                }
        }
    }
    return {};
} 