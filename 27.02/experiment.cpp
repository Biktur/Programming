#include<iostream>
#include<random>

using namespace std;

mt19937 rnd(time(0));

unsigned long long p = 998244353;

long long bin_pow(long long q, long long p, long long k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * q) % p, p, k / 2) * (k % 2 ? q : 1)) % p;
}

long long ord(long long a) {
        long long res = p - 1, l = p - 1;
        for (long long i = 2; i * i <= p - 1; ++i) {
                if (l % i == 0)
                        while (l % i == 0) {
                                l /= i;
                                if (bin_pow(a, p, res / i) == 1)
                                        res /= i;
                        }
        }
        if (l != 1 && bin_pow(a, p, res / l) == 1)
                res /= l;
        return res;
}

int main() {
	vector<long long> h = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271};
	long long p;
	for (long long l = 8388609; 1 ; l += 8388608) {
                if (l % 2 == 0)
                        continue;
                unsigned long long s = 0, d = l - 1;
                while (d % 2 == 0)
                        s++, d /= 2;
                bool z = 1;
                for (long long i : h) {
                        if (i >= l)
                                continue;
                        unsigned long long k = bin_pow(i, l, d);
                        bool f = 1;
                        if  (k == 1)
                                f = 0;
                        for (int j = 0; j < s + 1; ++j) {
                                if (k == l - 1) {
                                        f = 0;
                                        break;
                                }
                                k = (k * 1ull * k) %l;
                        }
                        if (f) {
                                z = 0;
                                break;
                        }
                }
                if (z) {
                        p = l;
                        break;
                }
	}
	cout << p << endl;
}
