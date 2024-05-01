// g++ -std=c++17 main.cpp -o sha256

#include <stdio.h>
#include <chrono>

#include "sha256.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    time_point<system_clock> start, end;
    duration<double> elapsed_seconds;

    string input = "";
    if (argc < 2) { printf("ERROR: No input string given"); return 1; }
    else { for (int i = 1; i < argc; i++) { input += argv[i]; } }

    start = system_clock::now();
    string out = hash256(input);
    end = system_clock::now();
    elapsed_seconds = end - start;

    printf("%s\n", out.c_str());
    printf("elapsed time: %fs\n", (float)elapsed_seconds.count());

    return 0;
}
