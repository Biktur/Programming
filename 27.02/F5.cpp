
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

unsigned bin_p(unsigned q, unsigned k) {
        if (k == 0)
                return 1;
        return (bin_p(q * q, k / 2) * (k % 2 ? q : 1));
}

unsigned l = 18;
unsigned m = 262144;
unsigned d = bin_pow((unsigned)(m), p - 2);
unsigned x = bin_pow(3, 119 * (1 << (23 - l)));
vector<unsigned> r(m);

void build_r() {
	unsigned t = 1;
	for (unsigned i = 0; i < m; ++i, t = (t * 1ull * x) % p)
        	r[i] = t;
}

unsigned invert (unsigned a) {
	unsigned res = 0;
	for (unsigned i = 0; i < l; ++i)
		res += ((a >> i) & 1) << (l - i - 1);
	return res;
}

vector<unsigned> fft (vector<unsigned> v0, bool rev = 0) {
	if (rev)
		reverse(r.begin() + 1, r.end());
	vector<unsigned> v = v0;
	for (unsigned i = 0; i < m; ++i)
		if (i < invert(i))
			swap(v[i], v[invert(i)]);
	for (unsigned i = 0, step = 1, power = m / 2; i < l; ++i, step *= 2, power /= 2)
		for (unsigned j = 0; j < m; j += 2 * step) 
			for (unsigned k = 0; k < step; ++k) {
				unsigned a = j + k, b = j + k + step;
				unsigned x = (v[a] + v[b] * 1ull * r[k * power]) % p, y = (v[a] + v[b] * 1ull * r[k * power + m / 2]) % p;
				v[a] = x; v[b] = y;
			}
	if (rev) {
		reverse(r.begin() + 1, r.end());
		for (unsigned i = 0; i < m; ++i)
			v[i] = (v[i] * 1ull * d) % p;
	}
	return v;
}

vector<unsigned> dot (vector<unsigned> v1, vector<unsigned> v2) {
	vector<unsigned> v(m);
	for (unsigned i = 0; i < m; ++i)
		v[i] = (v1[i] * 1ull * v2[i]) % p;
	return v;
}

int main() {
	ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
	build_r();
	unsigned o, k;
	string s, p;
	cin >> o >> k >> s >> p;
	unsigned z = s.size(), h = p.size();
	vector<unsigned> v(m), t(m), u(m), w(m);
	for (unsigned i = 0; i < h; ++i)
		w[h - 1] += (s[i] == 'o') * o + (s[i] == 'k') * k;
	for (unsigned i = h; i < z; ++i)
		w[i] = w[i - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k - (s[i - h] == 'o') * o - (s[i - h] == 'k') * k;
	for (unsigned i = 0; i < z; ++i)
		v[i] = (s[i] == 'o');
	for (unsigned i = 0; i < h; ++i)
		t[i] = (p[h - i - 1] == 'o') + (p[h - i - 1] == '?');
	v = fft(dot(fft(v), fft(t)), 1);
	for (unsigned i = 0; i < z; ++i)
		u[i] += v[i];
	for (unsigned i = 0; i < z; ++i)
                v[i] = (s[i] == 'k');
        for (unsigned i = 0; i < h; ++i)
                t[i] = (p[h - i - 1] == 'k') + (p[h - i - 1] == '?');
        v = fft(dot(fft(v), fft(t)), 1);
        for (unsigned i = 0; i < z; ++i)
                u[i] += v[i];
	vector<unsigned> dp(m);
	dp[h - 1] = w[h - 1] / bin_p(2, min(h - u[h - 1], 31u));
	for (unsigned i = h; i < z; ++i) {
		if (i < h * 2 - 1)
			dp[i] = max(dp[i - 1], w[i] / bin_p(2, min(h - u[i], 31u)));
		else
			dp[i] = max(dp[i - 1], w[i] / bin_p(2, min(h - u[i], 31u)) + dp[i - h]);
	}
	cout << dp[z - 1] << endl;
}



