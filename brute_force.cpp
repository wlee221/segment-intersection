/*
 * This program vertifies red blue segment test files using brute-force algorithm. 
 *
 * ! @author William Lee
 */

#include <iostream>
#include <fstream>
#include "classes/point.h"
using namespace std;

bool vertify_test_file(string);

int main(int argc, char* argv[]) {
    if (argc < 2) 
        cerr << "Usage: " << argv[0] << " <file1 file2 ...>" << endl;
    for (int i = 1; i < argc; ++i) 
        vertify_test_file(argv[i]);
    
    Point p = Point(100, 100);
    Point q = Point(200, 200);
    cout << (p < q) << endl;
}

bool vertify_test_file(string file_name) {
    ifstream input(file_name); 
    if (input.is_open()){
        int m, n, k;
        cout << "Testing " << file_name << "..." << endl;
    } else {
        cerr << endl << "ERROR: file " << file_name << " cannot be opened." << endl;
    }
    return true;
}
