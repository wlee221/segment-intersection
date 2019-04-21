/*
 * SI4: verify that red segments are non-crossing
 *
 * Author:  William Lee
 * Class:   Comp 651
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono> 
#include "impl/verify_red.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) 
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;

    // read arguments:
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    vector<Flag> flags; // store flags in a vector

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k; // m: # red segments, n: # blue segments, k: # expected red/blue crossing
        int px, py, rx, ry; // (px, py) and (rx, ry) store two endpoints of each segments

        input >> m >> n >> k;

        for (int i = 0; i < m; i++) {
            input >> px >> py >> rx >> ry;
            Segment s = Segment(Point(px, py), Point(rx, ry), Color::red);
            flags.push_back(Flag(s, s.p(), FlagType::start));
            flags.push_back(Flag(s, s.q(), FlagType::terminal));
        }

        sort(flags.begin(), flags.end());
        auto start = chrono::high_resolution_clock::now(); // start timer

        // if there exists intersection, we report the crossing pair. Otherwise, return an empty pair.
        optional<pair<Segment, Segment>> intersection; 
        for (int i = 0; i < num_execution; ++i) {
            intersection = sweep_line(flags);
        }

        auto stop = chrono::high_resolution_clock::now(); // end timer
        auto duration = chrono::duration<float, micro>(stop - start);

        if (intersection.has_value()) {
            cerr << "ERROR: intersection was found: " << intersection.value().first
                 << ", " << intersection.value().second << "." << endl;
        } else {
            cout << "VERIFIED" << endl;
        }

        cout << "Run time = " << duration.count() / (float) num_execution << " microseconds" << endl;
    } else {
        cerr << "File could not be opened." << endl;
    }
    return 0;
}
