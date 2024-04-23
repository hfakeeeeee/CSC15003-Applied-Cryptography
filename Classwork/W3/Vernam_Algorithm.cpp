/* Prefix 
a1 = 10010
a2 = 1001100
a3 = 11
a4 = 0
a5 = 1000
a6 = 101
a7 = 1001101
a8 = 100111

L(f) = 2.21

*/

#include <iostream>
#include <string>
using namespace std;

string keyGenerate(int n) {
    string key = "";

    for (int i = 0; i < n; i++) {
        key += (char)(rand() % 256);
    }

    return key;
}

string vernamEncrypt(string plaintext, string key) {
    string cipherText = "";
    
    for (int i = 0; i < key.length(); i++) {
        char c = plaintext[i] ^ key[i];
        cipherText += c;
    }

    return cipherText;
}

string vernamDecrypt(string ciphertext, string key) {
    string plainText = "";

    for (int i = 0; i < key.length(); i++) {
        char c = ciphertext[i] ^ key[i];
        plainText += c;
    }

    return plainText;
}


int main()
{
    srand(time(NULL));
    string p = "lecungtien", c = "", k = "";

    for (int i = 0; i < 20; i++) {
        k = keyGenerate(p.length());
        
        c = vernamEncrypt(p, k);
        cout << "cipher text[" << i << "]: " << c << endl;

        p = vernamDecrypt(c, k);
        cout << "plain text[" << i << "]: " << p << endl << endl;
    }
}

