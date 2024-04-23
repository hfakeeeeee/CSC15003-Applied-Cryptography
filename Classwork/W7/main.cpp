#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef unsigned long long ull;

ull modular_pow(ull base, ull exponent, ull modulus) {
    if (modulus == 1) return 0;
    ull result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

bool miller_rabin_test(ull n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    ull d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    for (int i = 0; i < k; i++) {
        ull a = 2 + rand() % (n - 4);
        ull x = modular_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (ull r = 1; r <= d; r <<= 1) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    unsigned int n;
    int k;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Nhap so lan: ";
    cin >> k;

    if (miller_rabin_test(n, k)) {
        cout << n << " co the la so nguyen to" << endl;
    } else {
        cout << n << " la hop so" << endl;
    }

    return 0;
}
