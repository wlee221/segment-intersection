#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono> 
#include "classes/point.hpp"
#include "classes/segment.hpp"
#include "classes/flag.hpp"
using namespace std;

bool sort_flags(vector<Flag> &flags);

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
            Color c = (i < m) ? Color::red : Color::blue;
            Segment s = Segment(Point(px, py), Point(rx, ry), c);
            flags.push_back(Flag(s, s.p(), FlagType::start));
            flags.push_back(Flag(s, s.q(), FlagType::terminal));
        }
        
        auto start = chrono::high_resolution_clock::now(); 

        for (int i = 0; i < num_execution; ++i)
            sort_flags(flags);

        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration<float>(stop - start);

        for (const auto &f : flags) 
            cout << f << endl;

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;
    } else {
        cerr << "File could not be opened";
    }

    return 0;
}

bool sort_flags(vector<Flag> &flags) {
    sort(flags.begin(), flags.end());
}