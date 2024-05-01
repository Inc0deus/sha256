// g++ -std=c++17 main.cpp -o sha256

#include <stdio.h>
#include <chrono>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include <time.h>

#include "sha256.h"

using namespace std;
using namespace std::chrono;

double benchmark(string data_path) {
    srand(time(NULL));

    ifstream data_file;
    data_file.open(data_path);
    
    string data = "";
    vector<string> data_set{};
    size_t start = 0;
    size_t block = 1000;

    if (!data_file.is_open()) {
        printf("ERROR: Could not open data file %s\n", data_path.c_str());
        return -1;
    }

    while(data_file) {
        string s;
        data_file >> s;
        data += s;
    }

    if (data.length() < block) {
        printf("ERROR: The data file is too short %s\n", data_path.c_str());
        return -1;
    }

    // create data set: 100 string of 1000 characters
    while(data_set.size() < 100) {
        start = rand() % (data.length() - block);
        data_set.push_back(data.substr(start, block));
    }

    time_point<system_clock> timer_start, timer_end;
    duration<double> elapsed_seconds;

    timer_start = system_clock::now();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            hash256(data_set[j]);
        }
    }
    timer_end = system_clock::now();
    elapsed_seconds = timer_end - timer_start;

    return elapsed_seconds.count();
}

int main(int argc, char *argv[]) {
    time_point<system_clock> start, end;
    duration<double> elapsed_seconds;

    string input = "";
    if (argc < 2) { printf("ERROR: No input string given"); return 1; }
    else { for (int i = 1; i < argc; i++) { input += argv[i]; } }

    printf("%f\n", (float)benchmark("Le_rouge_et_le_noir.txt"));

    start = system_clock::now();
    string out = hash256(input);
    end = system_clock::now();
    elapsed_seconds = end - start;

    printf("%s\n", out.c_str());
    printf("elapsed time: %fs\n", (float)elapsed_seconds.count());

    return 0;
}
