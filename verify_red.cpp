#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <optional>
#include <chrono> 
#include <map>
#include "classes/point.hpp"
#include "classes/segment.hpp"
#include "classes/flag.hpp"
using namespace std;

optional<pair<Segment, Segment>> sweep_line(vector<Flag> &flags);

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

        optional<pair<Segment, Segment>> intersection;
        for (int i = 0; i < num_execution; ++i) {
            intersection = sweep_line(flags);
        }

        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration<float>(stop - start);

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

void insert_segment(multimap<int, Segment> &active, const Segment s) {
    // inserts segment s with s.p().y() as its key value.
    active.insert({s.p().y(), s});
}

optional<pair<Segment, Segment>> sweep_line(vector<Flag> &flags) {
    multimap<int, Segment> active;  

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
                return make_pair(above, f.s());
            if (intersects(below, f.s()))
                return make_pair(below, f.s());
            insert_segment(active, f.s());
        } else {
            // need to remove the segment of f. 
            int key = f.s().p().y(); // get the left endpoint, which was used as a key when the start flag was added.
            auto key_range = active.equal_range(key); // there might be multiple segments at key, so get a range of elements.
            auto to_remove = std::find(key_range.first, key_range.second, pair<const int, Segment> (key, f.s()));
            if (to_remove == active.end()) 
                cerr << "ERROR: Could not find segment to remove" << endl;

            Segment s = (*to_remove).second;
            Segment below = (*prev(to_remove)).second;
            Segment above = (*next(to_remove)).second;
            if (intersects(below, above)) 
                return make_pair(below, above);
            active.erase(to_remove);

        }
    }
    return {};
} 