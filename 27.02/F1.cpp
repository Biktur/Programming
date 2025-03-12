#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

const long long p = 998244353;

long long bin_pow(long long q, long long k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * 1ull * q) % p, k / 2) * 1ull * (k % 2 ? q : 1)) % p;
}

long long l = 18;
long long m = 262144;
long long d = bin_pow((long long)(m), p - 2);
long long x = bin_pow(3, 119 * (1 << (23 - l)));
vector<long long> r(m);

void build_r() {
	long long t = 1;
	for (long long i = 0; i < m; ++i, t = (t * 1ull * x) % p)
        	r[i] = t;
}

long long invert (long long a) {
	long long res = 0;
	for (long long i = 0; i < l; ++i)
		res += ((a >> i) & 1) << (l - i - 1);
	return res;
}

vector<long long> fft (vector<long long> v0, bool rev = 0) {
	if (rev)
		reverse(r.begin() + 1, r.end());
	vector<long long> v = v0;
	for (long long i = 0; i < m; ++i)
		if (i < invert(i))
			swap(v[i], v[invert(i)]);
	for (long long i = 0, step = 1, power = m / 2; i < l; ++i, step *= 2, power /= 2)
		for (long long j = 0; j < m; j += 2 * step) 
			for (long long k = 0; k < step; ++k) {
				long long a = j + k, b = j + k + step;
				long long x = (v[a] + v[b] * 1ull * r[k * power]) % p, y = (v[a] + v[b] * 1ull * r[k * power + m / 2]) % p;
				v[a] = x; v[b] = y;
			}
	if (rev) {
		reverse(r.begin() + 1, r.end());
		for (long long i = 0; i < m; ++i)
			v[i] = (v[i] * 1ull * d) % p;
	}
	return v;
}

vector<long long> dot (vector<long long> v1, vector<long long> v2) {
	vector<long long> v(m);
	for (long long i = 0; i < m; ++i)
		v[i] = (v1[i] * 1ull * v2[i]) % p;
	return v;
}

int main() {
	build_r();
	long long o, k;
	string s, p;
	cin >> o >> k >> s >> p;
	vector<long long> v(m), t(m), c(m), w(m);
	for (long long i = 0; i < p.size(); ++i)
		w[p.size() - 1] += (s[i] == 'o') * o + (s[i] == 'k') * k;
	for (long long i = p.size(); i < s.size(); ++i)
		w[i] = w[i - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k - (s[i - p.size()] == 'o') * o - (s[i - p.size()] == 'k') * k;
	for (long long i = 0; i < s.size(); ++i)
		v[i] = (s[i] == 'o');
	for (long long i = 0; i < p.size(); ++i)
		t[i] = (p[p.size() - i - 1] == 'o') + (p[p.size() - i - 1] == '?');
	v = fft(dot(fft(v), fft(t)), 1);
	for (long long i = 0; i < s.size(); ++i)
		c[i] += v[i];
	for (long long i = 0; i < s.size(); ++i)
                v[i] = (s[i] == 'k');
        for (long long i = 0; i < p.size(); ++i)
                t[i] = (p[p.size() - i - 1] == 'k') + (p[p.size() - i - 1] == '?');
        v = fft(dot(fft(v), fft(t)), 1);
        for (long long i = 0; i < s.size(); ++i)
                c[i] += v[i];
	vector<long long> dp(m);
	dp[p.size() - 1] = (w[p.size() - 1] >> (p.size() - c[p.size() - 1]));
	for (long long i = p.size(); i < s.size(); ++i) {
		if (i < p.size() * 2 - 1)
			dp[i] = max(dp[i - 1], 1ll * (w[i] >> (p.size() - c[i])));
		else
			dp[i] = max(dp[i - 1], 1ll * (w[i] >> (p.size() - c[i])) + dp[i - p.size()]);
	}
	cout << dp[s.size() - 1] << endl;
}

