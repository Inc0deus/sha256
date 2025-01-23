// g++ -std=c++17 main.cpp -o sha256

#include <iostream>
#include "sha256.h"

int main(int argc, char *argv[]) {
    string input = "";
    if (argc < 2) { printf("ERROR: No input string given"); return 1; }
    else { for (int i = 1; i < argc; i++) { input += argv[i]; } }   // concatenate input

    std::cout << hash256(input) << std::endl;;

    return EXIT_SUCCESS;
}
