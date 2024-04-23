#include "Header.h"
#include "Table.h"

int main() {
    string m = "hcmusfit";
    string k = "12345678";

    cout << "Plain text: " << m << endl;
    cout << "Key: " << k << endl;

    string c_iv_hex = CBCRandomEnc(m, k);
    string cipherText = convertBinarytoHex1(c_iv_hex);
    cout << "Encrypted text: " << cipherText << endl;

    string decrypted_m = CBCRandomDec(c_iv_hex, k);
    string original_message = convertHextoText(convertBinarytoHex2(decrypted_m));
    cout << "Decrypted text: " << original_message << endl;

    return 0;
}