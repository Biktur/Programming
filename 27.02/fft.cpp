#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

const unsigned p = 998244353;

unsigned bin_pow(unsigned q, unsigned k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * 1ull * q) % p, k / 2) * 1ull * (k % 2 ? q : 1)) % p;
}

int l = *;
int m = *;
unsigned d = bin_pow(unsigned(m), p - 2);
unsigned x = bin_pow(3, 119 * (1 << (23 - l)));
vector<unsigned> r(m);

void build_r() {
	int t = 1;
	for (int i = 0; i < m; ++i, t = (t * 1ull * x) % p)
        	r[i] = t;
}

int invert (int a) {
	int res = 0;
	for (int i = 0; i < l; ++i)
		res += ((a >> i) & 1) << (l - i - 1);
	return res;
}

vector<unsigned> fft (vector<unsigned> v0, bool rev = 0) {
	if (rev)
		reverse(r.begin() + 1, r.end());
	vector<unsigned> v = v0;
	for (int i = 0; i < m; ++i)
		if (i < invert(i))
			swap(v[i], v[invert(i)]);
	for (int i = 0, step = 1, power = m / 2; i < l; ++i, step *= 2, power /= 2)
		for (int j = 0; j < m; j += 2 * step) 
			for (int k = 0; k < step; ++k) {
				int a = j + k, b = j + k + step;
				unsigned x = (v[a] + v[b] * 1ull * r[k * power]) % p, y = (v[a] + v[b] * 1ull * r[k * power + m / 2]) % p;
				v[a] = x; v[b] = y;
			}
	if (rev) {
		reverse(r.begin() + 1, r.end());
		for (int i = 0; i < m; ++i)
			v[i] = (v[i] * 1ull * d) % p;
	}
	return v;
}

vector<unsigned> dot (vector<unsigned> v1, vector<unsigned> v2) {
	vector<unsigned> v(m);
	for (int i = 0; i < m; ++i)
		v[i] = (v1[i] * 1ull * v2[i]) % p;
	return v;
}
