#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono> 
#include "classes/point.h"
#include "classes/segment.h"
using namespace std;

int count_intersections(vector<Segment> &red, vector<Segment> &blue);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file_path> <number of executions>" << endl;
        return 0;
    }
    // read input:
    const string file_name = argv[1];
    const int num_execution = stoi(argv[2]);

    vector<Segment> red;
    vector<Segment> blue;  

    // read file 
    ifstream input(file_name);
    if (input.is_open()) {
        int m, n, k;
        int px, py, rx, ry;

        input >> m >> n >> k;

        for (int i = 0; i < m; i++) {
            input >> px >> py >> rx >> ry;
            red.push_back(Segment(Point(px, py), Point(rx, ry), true));
        }

        for (int i = 0; i < n; i++) {
            input >> px >> py >> rx >> ry;
            blue.push_back(Segment(Point(px, py), Point(rx, ry), false));
        }

        auto start = chrono::high_resolution_clock::now(); 

        int k_test;
        for (int i = 0; i < num_execution; ++i)
            k_test = count_intersections(red, blue);

        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration<float, milli>(stop - start);

        if (k == k_test)
            cout << "VERIFIED" << endl;
        else
            cout << "ERROR: expected k = " << k << " but got " << k_test << "." << endl;

        cout << "Run time = " << duration.count() / (float) num_execution << " ms" << endl;

    } else {
        cerr << "ERROR: File could not be opened.";
    }
}

int count_intersections(vector<Segment> &red, vector<Segment> &blue) {
    int k = 0;
    for (const auto &red_seg : red) 
        for (const auto &blue_seg : blue) 
            if (intersects(red_seg, blue_seg)) 
                ++k;
    return k;
}