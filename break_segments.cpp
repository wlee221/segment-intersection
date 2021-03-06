/*
 * SI5: Breaks red segments such that none contains any flag point. 
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
#include "impl/break_segments.hpp"
using namespace std;

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
            broken_segments = break_segments(flags, Color::red);
        }

        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration<float, micro>(stop - start);

        std::vector<Segment> red;
        if (broken_segments.has_value()) {  
            red = broken_segments.value();
            for (const auto &s: red) {
                cout << s << endl;
            }
        } else {
            cerr << "Error: Intersection detected." << endl;
        }

        cout << "Run time = " << duration.count() / (float) num_execution << " microseconds" << endl;
    } else {
        cerr << "File could not be opened." << endl;
    }
    return 0;
}