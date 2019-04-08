/*
 * This program vertifies red blue segment test files using brute-force algorithm. 
 *
 * ! @author William Lee
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "classes/point.h"
#include "classes/segment.h"
#include "classes/flag.h"
using namespace std;

bool sort_flags(const string&);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file1>" << endl;
        return 1;
    }
    sort_flags(argv[1]);
    return 0;
}

bool sort_flags(const string &file_name) {
    vector<Segment> red;
    vector<Segment> blue;
    vector<Flag> flags;
    ifstream input(file_name); 
    if (input.is_open()){
        int m, n, k;
        input >> m >> n >> k;

        int px, py, rx, ry;

        // TODO: check if we should do a copy of s when we add flags.
        for (int i = 0; i < m; i++) {
            input >> px >> py >> rx >> ry;
            Segment s = Segment(Point(px, py), Point(rx, ry), true);
            red.push_back(s);
            flags.push_back(Flag(s, s.p(), true));
            flags.push_back(Flag(s, s.q(), false));
        }

        for (int i = 0; i < n; i++) {
            input >> px >> py >> rx >> ry;
            Segment s = Segment(Point(px, py), Point(rx, ry), false);
            blue.push_back(Segment(s));
            flags.push_back(Flag(s, s.p(), true));
            flags.push_back(Flag(s, s.q(), false));
        }

        sort(flags.begin(), flags.end());
        for (const auto &f : flags) {
            cout << f;
        }     
        
    } else {
        cerr << endl << "ERROR: file " << file_name << " cannot be opened." << endl;
    }
    return true;
}
