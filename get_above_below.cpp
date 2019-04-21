/*
 * SI6: Compute segements above and below each flag
 *
 * Author:  William Lee
 * Class:   Comp 651
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono> 
#include "impl/get_above_below.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) 
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;

    // read arguments
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    vector<Flag> flags; // store flags in a vector

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k; // m: # red segments, n: # blue segments, k: # expected red/blue crossing
        int px, py, rx, ry; // (px, py) and (rx, ry) store two endpoints of each segments

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
        auto start = chrono::high_resolution_clock::now(); // start timer

        map<Flag, AboveBelow> flag_above_below; // maps each flag to an AboveBelow class
        for (int i = 0; i < num_execution; ++i) {
            flag_above_below = get_above_below(flags);
        }

        auto stop = chrono::high_resolution_clock::now(); // end timer
        auto duration = chrono::duration<float, micro>(stop - start);

        for (auto it = flag_above_below.begin(); it != flag_above_below.end(); ++it) 
            cout << it->first << endl << "AboveBelow: " << it->second << endl << endl;

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;
    } else {
        cerr << "File could not be opened." << endl;
    }
    return 0;
}