#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <sstream>
#include <random>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <bitset>
#include <unordered_map>
using namespace std;

string convertDecimalToBinary(int decimal);
int convertBinaryToDecimal(string bin);
string convertStringtoBinary(string str);
void createMap(unordered_map<string, char>* um);
string convertBinarytoHex1(string bin);
string convertBinarytoHex2(string bin);
string convertHextoBinary(string hexString);
string convertHextoText(string hex);
string shift_left_once(string key_chunk);
string shift_left_twice(string key_chunk);
void generate_keys(string key);
string DES(string pt);
string decryption(string ct);
string CBCRandomEnc(string plaintext, string key);
string CBCRandomDec(string c_iv_hex, string k);
string Xor(string a, string b);

#endif