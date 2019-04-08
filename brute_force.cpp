/*
 * This program vertifies red blue segment test files using brute-force algorithm. 
 *
 * ! @author William Lee
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "classes/point.h"
#include "classes/segment.h"
using namespace std;

bool vertify_test_file(string);

int main(int argc, char* argv[]) {
    if (argc < 2) 
        cerr << "Usage: " << argv[0] << " <file1 file2 ...>" << endl;
    for (int i = 1; i < argc; ++i) 
        vertify_test_file(argv[i]);
    
}

bool vertify_test_file(string file_name) {
    vector<Segment> red;
    vector<Segment> blue; 
    ifstream input(file_name); 
    if (input.is_open()){
        int m, n, k;
        input >> m >> n >> k;

        int px, py, rx, ry;
        for (int i = 0; i < m; i++) {
            input >> px >> py >> rx >> ry;
            red.push_back(Segment(Point(px, py), Point(rx, ry), true));
        }

        for (int i = 0; i < n; i++) {
            input >> px >> py >> rx >> ry;
            blue.push_back(Segment(Point(px, py), Point(rx, ry), false));
        }
        
        int n_intersections = 0;
        for (const auto &red_seg : red) 
            for (const auto &blue_seg : blue) 
                if (intersects(red_seg, blue_seg)) 
                    ++n_intersections;

        if (n_intersections == k) 
            cout << "VERIFIED" << endl;
        else
            cout << "ERROR: expected k = " << k << " but got " << n_intersections << "." << endl;
    } else {
        cerr << endl << "ERROR: file " << file_name << " cannot be opened." << endl;
    }
    return true;
}
