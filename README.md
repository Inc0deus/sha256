# sha256 implementation

This is an implementation of the sha256 hash function in C++ (in one header "sha256.h").
The code is not made to be particularly fast so it is not intended for real use cases, only for learning. The tests I did showed that the hashing took approximately 0.00066s (tests made on 100 strings of 1000 characters 100 times).

The main function is "hash265", it takes a string (unicode characters) and return another string (hexadecimal characters - 0123456789abcdef).
"main.cpp" is for demo purposes and is not usefull to the hashing function.
