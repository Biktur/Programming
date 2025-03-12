#include<iostream>
#include<vector>

using namespace std;

long long bin_pow(long long q, long long p, long long k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * q) % p, p, k / 2) * (k % 2 ? q : 1)) % p;
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<long long> v(k);
	long long s = 0;
	for (int i = 1; i < k; ++i)
		v[i] = bin_pow(i, k, n);
	for (int i = 1; i < k; ++i)
		for (int j = i; j < k; ++j)
			if ((v[i] + v[j]) % k)
				s ++;
	cout << s << endl;
}
