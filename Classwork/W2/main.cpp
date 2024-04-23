#include <iostream>
#include <string>

using namespace std;

string vingere_cipher_enc(string k, string m) {
    string output = "";
    
    for (int i = 0, j = 0; i < m.length(); i++) {
        char c = m[i];

        output += (c + k[j] - 2 * 'a') % 26 + 'a';
        j = (j + 1) % k.length();
    }

    return output;
}

string vingere_cipher_dec(string k, string c) {
    string output = "";

    for (int i = 0, j = 0; i < c.length(); i++) {
        char m = c[i];

        output += (m - k[j] + 26) % 26 + 'a';
        j = (j + 1) % k.length();
    }

    return output;
}

int main() {
	string m = "helloworld", k = "huy", c = "";
	cout << "orginal message: " << m << endl;
	c = vingere_cipher_enc(k, m);
	cout << "encrypted message: " << c << endl;
	m = vingere_cipher_dec(k, c);
	cout << "decrypted message: " << m << endl;
}