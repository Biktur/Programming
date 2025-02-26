#include<iostream>
#include<random>
#include<ctime>
#include<algorithm>

using namespace std;

mt19937 rnd(time(0));

const unsigned p = 1 << 31;
const int m = 30;

unsigned long long bin_pow(unsigned long long q, unsigned long long k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * q) % p, k / 2) * (k % 2 ? q : 1)) % p;
}

int main() {
	int n;
	cin >> n;
	vector<unsigned> v;
	for (int i = 0; i < m; ++i)
		while (1) {
			unsigned a = rnd() % p;
			if ((a & 1) && !(count(v.begin(), v.end(), a))) {
				v.push_back(a);
				break;
			}
		}
	for (int i = 0; i < min(m, n); ++i)
		cout << v[i] << endl;
	for (int i = 0; i < n - m; ++i) 
		cout << 2 * i << endl;
	vector<unsigned> u;
	for (int i = 0; i < n / 2; ++i) {
		int a;
		cin >> a;
		if (a & 1)
			u.push_back(a);
	}
	sort(u.begin(), u.end());
	for (auto j : v) {
		unsigned r = (u[0] * 1ull * bin_pow(j, p / 2 - 1)) % p;
		for (auto k : v)
			if (k != j && binary_search(u.begin(), u.end(), (k * 1ull * r) % p)) {
				cout << r << endl;
				return 0;
			}
	}
}
			

