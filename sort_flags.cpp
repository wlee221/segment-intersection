/*
 * SI3: Sort flags and prints the list of the flags in sorted order
 *
 * Author:  William Lee
 * Class:   Comp 651
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> 
#include "impl/sort_flags.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) 
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;
    
    // read arguments:
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    // store flags in a vector.
    vector<Flag> flags;

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k; // m: # red segments, n: # blue segments, k: # expected red/blue crossing
        int px, py, rx, ry; // (px, py) and (rx, ry) store two endpoints of each segments

        input >> m >> n >> k;

        for (int i = 0; i < m + n; i++) {
            input >> px >> py >> rx >> ry;
            Color c = (i < m) ? Color::red : Color::blue;
            Segment s = Segment(Point(px, py), Point(rx, ry), c);
            flags.push_back(Flag(s, s.p(), FlagType::start));
            flags.push_back(Flag(s, s.q(), FlagType::terminal));
        }
        
        auto start = chrono::high_resolution_clock::now(); // start time

        for (int i = 0; i < num_execution; ++i) 
            sort_flags(flags); 

        auto stop = chrono::high_resolution_clock::now(); // end timer
        auto duration = chrono::duration<float, micro>(stop - start);

        for (const auto &f : flags) 
            cout << f << endl; // print sorted flags

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;
    } else {
        cerr << "File could not be opened";
    }

    return 0;
}
