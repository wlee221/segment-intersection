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
