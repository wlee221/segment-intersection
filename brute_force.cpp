/*
 * SI1: Counts red/blue crossing using brute force algorithm. 
 *
 * Author:  William Lee
 * Class:   Comp 651
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono> 
#include "impl/brute_force.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) 
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;

    // read arguments:
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    // store red/blue segments in vectors
    vector<Segment> red;
    vector<Segment> blue;  

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k; // m: # red segments, n: # blue segments, k: # expected red/blue crossing
        int px, py, rx, ry; // (px, py) and (rx, ry) store two endpoints of each segments

        input >> m >> n >> k;

        for (int i = 0; i < m + n; i++) {
            input >> px >> py >> rx >> ry;
            if (i < m)
                red.push_back(Segment(Point(px, py), Point(rx, ry), Color::red));
            else
                blue.push_back(Segment(Point(px, py), Point(rx, ry), Color::blue));
        }
        auto start = chrono::high_resolution_clock::now(); // start timer

        int k_test; // # red/blue crossing computed by brute force algorithm
        for (int i = 0; i < num_execution; ++i) 
            k_test = count_intersections(red, blue);

        auto stop = chrono::high_resolution_clock::now(); // end timer
        auto duration = chrono::duration<float, micro>(stop - start);

        if (k == k_test)
            cout << "VERIFIED" << endl;
        else
            cout << "ERROR: expected k = " << k << " but got " << k_test << "." << endl;

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;

    } else {
        cerr << "ERROR: File could not be opened.";
    }
    return 0;
}