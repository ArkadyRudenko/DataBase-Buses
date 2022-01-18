#include <iostream>

#include "GenereateLongTest.h"

using namespace std;

const int N = 2000;
const int BUS = 100;

void GenerateStops(stringstream &file) {
    static int stop = 0;
    for (int i = 0, k = 0; i < 50; i++) {
        file << "Name" << i + stop;
        if (i != 49) {
            file << " - ";
        }

    }
    file << '\n';
    stop += 18;
}

void Generate(stringstream &file) {
    file << 2000 << '\n';
    for (int i = 0; i < N - BUS; i++) {
        file << "Stop " << ("Name" + to_string(i)) << ": " << rand() % 180 << ", " << rand() % 180 << '\n';
    }
    for (int i = 0; i < BUS; i++) {
        file << "Bus " << i << ": ";
        GenerateStops(file);
    }
}

void GenerateReq(stringstream & file) {
    file << BUS << '\n';
    for (int i = 0; i < BUS; ++i) {
        file << "Bus " << i << '\n';
    }
}
