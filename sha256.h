#pragma once

#include <vector>
#include <bitset>

using namespace std;

typedef size_t length_t, position_t;

string hex_digit = "0123456789abcdef";
string bin32_to_hex(bitset<32> bin) {
    string hex_str = "";
    for (position_t i = 0; i < 32; i+=4) {
        hex_str = hex_digit[bin[i+3]*8 + bin[i+2]*4 +bin[i+1]*2 + bin[i]] + hex_str; 
    }
    return hex_str;
}

bitset<32> hex_to_bin32(string hex) {
    string bin = "";
    for (int i = 0; i < 8; i++) {
        switch(hex[i]) {
            case '0': bin += "0000"; break;
            case '1': bin += "0001"; break;
            case '2': bin += "0010"; break;
            case '3': bin += "0011"; break;
            case '4': bin += "0100"; break;
            case '5': bin += "0101"; break;
            case '6': bin += "0110"; break;
            case '7': bin += "0111"; break;
            case '8': bin += "1000"; break;
            case '9': bin += "1001"; break;
            case 'a': bin += "1010"; break;
            case 'b': bin += "1011"; break;
            case 'c': bin += "1100"; break;
            case 'd': bin += "1101"; break;
            case 'e': bin += "1110"; break;
            case 'f': bin += "1111"; break;
        }
    }
    return bitset<32>(bin);
}

// BASIC OPERATIONS
#define SHR(x, n)  (x >> n)                     // SHIFT RIGHT
#define ROTR(x, n) ((x >> n) | (x << (32-n)))   // ROTATE RIGHT

bitset<32> ADD(vector<bitset<32> > bins) {  // ADD modulo 2^32
    uint32_t RES = 0;
    for(position_t i = 0; i < bins.size(); i++) {
        RES += bins[i].to_ullong();
    }
    return bitset<32>(RES);
}

// FUNCTIONS
#define sigma_0(x) ((ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3)))
#define sigma_1(x) ((ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10)))

#define SIGMA_0(x) ((ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22)))
#define SIGMA_1(x) ((ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25)))

#define Ch(x, y, z) ((x & y) ^ (~x & z))
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

// CONSTANTS
// vector<double> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311};
// string H_0[8] = {"6a09e667", "bb67ae85", "3c6ef372", "a54ff53a", "510e527f", "9b05688c", "1f83d9ab", "5be0cd19"};
// string K[64] = {
//     "428a2f98", "71374491", "b5c0fbcf", "e9b5dba5", "3956c25b", "59f111f1", "923f82a4", "ab1c5ed5", 
//     "d807aa98", "12835b01", "243185be", "550c7dc3", "72be5d74", "80deb1fe", "9bdc06a7", "c19bf174", 
//     "e49b69c1", "efbe4786", "0fc19dc6", "240ca1cc", "2de92c6f", "4a7484aa", "5cb0a9dc", "76f988da", 
//     "983e5152", "a831c66d", "b00327c8", "bf597fc7", "c6e00bf3", "d5a79147", "06ca6351", "14292967", 
//     "27b70a85", "2e1b2138", "4d2c6dfc", "53380d13", "650a7354", "766a0abb", "81c2c92e", "92722c85", 
//     "a2bfe8a1", "a81a664b", "c24b8b70", "c76c51a3", "d192e819", "d6990624", "f40e3585", "106aa070", 
//     "19a4c116", "1e376c08", "2748774c", "34b0bcb5", "391c0cb3", "4ed8aa4a", "5b9cca4f", "682e6ff3", 
//     "748f82ee", "78a5636f", "84c87814", "8cc70208", "90befffa", "a4506ceb", "bef9a3f7", "c67178f2"
// };

string H_0[8] = {
    "01101010000010011110011001100111","10111011011001111010111010000101","00111100011011101111001101110010","10100101010011111111010100111010",
    "01010001000011100101001001111111","10011011000001010110100010001100","00011111100000111101100110101011","01011011111000001100110100011001",
};
string K[64] = {
    "01000010100010100010111110011000","01110001001101110100010010010001","10110101110000001111101111001111","11101001101101011101101110100101",
    "00111001010101101100001001011011","01011001111100010001000111110001","10010010001111111000001010100100","10101011000111000101111011010101",
    "11011000000001111010101010011000","00010010100000110101101100000001","00100100001100011000010110111110","01010101000011000111110111000011",
    "01110010101111100101110101110100","10000000110111101011000111111110","10011011110111000000011010100111","11000001100110111111000101110100",
    "11100100100110110110100111000001","11101111101111100100011110000110","00001111110000011001110111000110","00100100000011001010000111001100",
    "00101101111010010010110001101111","01001010011101001000010010101010","01011100101100001010100111011100","01110110111110011000100011011010",
    "10011000001111100101000101010010","10101000001100011100011001101101","10110000000000110010011111001000","10111111010110010111111111000111",
    "11000110111000000000101111110011","11010101101001111001000101000111","00000110110010100110001101010001","00010100001010010010100101100111",
    "00100111101101110000101010000101","00101110000110110010000100111000","01001101001011000110110111111100","01010011001110000000110100010011",
    "01100101000010100111001101010100","01110110011010100000101010111011","10000001110000101100100100101110","10010010011100100010110010000101",
    "10100010101111111110100010100001","10101000000110100110011001001011","11000010010010111000101101110000","11000111011011000101000110100011",
    "11010001100100101110100000011001","11010110100110010000011000100100","11110100000011100011010110000101","00010000011010101010000001110000",
    "00011001101001001100000100010110","00011110001101110110110000001000","00100111010010000111011101001100","00110100101100001011110010110101",
    "00111001000111000000110010110011","01001110110110001010101001001010","01011011100111001100101001001111","01101000001011100110111111110011",
    "01110100100011111000001011101110","01111000101001010110001101101111","10000100110010000111100000010100","10001100110001110000001000001000",
    "10010000101111101111111111111010","10100100010100000110110011101011","10111110111110011010001111110111","11000110011100010111100011110010"
};


string hash256(string input) {
    // PREPROCESSING
    length_t l = 8 * input.length();
    int N = (l + 64) / 512 + 1;
    length_t k = (N * 512 - 64) - (l + 1);

    string str_message = "";
    for(position_t i = 0; i < input.length(); i++) {
        str_message += bitset<8>(input[i]).to_string();
    }
    str_message += "1";
    for(length_t i = 0; i < k; i++) {
        str_message += "0";
    }
    str_message += bitset<64>(l).to_string();

    vector<bitset<512> > message_blocks;
    for(position_t i = 0; i < N; i++) {
        string message = "";
        for(position_t j = 0; j < 512; j++) {
            message += str_message[i * 512 + j];
        }
        message_blocks.push_back(bitset<512>(message));
    }

    // HASH COMPUTATION
    bitset<32> H[8];
    for(position_t i = 0; i < 8; i++) H[i] = bitset<32>(H_0[i]);
    bitset<32> T1, T2;
    bitset<32> a = H[0];
    bitset<32> b = H[1];
    bitset<32> c = H[2];
    bitset<32> d = H[3];
    bitset<32> e = H[4];
    bitset<32> f = H[5];
    bitset<32> g = H[6];
    bitset<32> h = H[7];

    for(position_t i = 0; i < N; i++) {
        bitset<32> W[64];
        for (position_t t = 0; t < 16; t++) {
            for (position_t j = 0; j < 32; j++) {
                W[t][32 - (j + 1)] = message_blocks[i][512 - (t * 32 + j + 1)];
            }
        }
        for (position_t t = 16; t < 64; t++) {
            W[t] = ADD({W[t-7], W[t-16], sigma_0(W[t-15]), sigma_1(W[t-2])});
        }

        a = H[0];
        b = H[1];
        c = H[2];
        d = H[3];
        e = H[4];
        f = H[5];
        g = H[6];
        h = H[7];

        for (position_t t = 0; t < 64; t++) {
            T1 = ADD({SIGMA_1(e), Ch(e, f, g), h, bitset<32>(K[t]), W[t]});
            T2 = ADD({SIGMA_0(a), Maj(a, b, c)});
            h = g;
            g = f;
            f = e;
            e = ADD({d, T1});
            d = c;
            c = b;
            b = a;
            a = ADD({T1, T2});
        }
        
        H[0] = ADD({a, bitset<32>(H[0])});
        H[1] = ADD({b, bitset<32>(H[1])});
        H[2] = ADD({c, bitset<32>(H[2])});
        H[3] = ADD({d, bitset<32>(H[3])});
        H[4] = ADD({e, bitset<32>(H[4])});
        H[5] = ADD({f, bitset<32>(H[5])});
        H[6] = ADD({g, bitset<32>(H[6])});
        H[7] = ADD({h, bitset<32>(H[7])});
    }

    string output = "";
    output += bin32_to_hex(bitset<32>(H[0]))
            + bin32_to_hex(bitset<32>(H[1]))
            + bin32_to_hex(bitset<32>(H[2]))
            + bin32_to_hex(bitset<32>(H[3]))
            + bin32_to_hex(bitset<32>(H[4]))
            + bin32_to_hex(bitset<32>(H[5]))
            + bin32_to_hex(bitset<32>(H[6]))
            + bin32_to_hex(bitset<32>(H[7]));

    return output;
}
