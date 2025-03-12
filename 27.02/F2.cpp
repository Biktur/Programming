#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

const long long unsigned p = 998244353;

long long unsigned bin_pow(long long unsigned q, long long unsigned k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * 1ull * q) % p, k / 2) * 1ull * (k % 2 ? q : 1)) % p;
}

long long unsigned bin_p(long long unsigned q, long long unsigned k) {
        if (k == 0)
                return 1;
        return (bin_p(q * q, k / 2) * (k % 2 ? q : 1));
}

long long unsigned l = 18;
long long unsigned m = 262144;
long long unsigned d = bin_pow((long long unsigned)(m), p - 2);
long long unsigned x = bin_pow(3, 119 * (1 << (23 - l)));
vector<long long unsigned> r(m);

void build_r() {
	long long unsigned t = 1;
	for (long long unsigned i = 0; i < m; ++i, t = (t * 1ull * x) % p)
        	r[i] = t;
}

long long unsigned invert (long long unsigned a) {
	long long unsigned res = 0;
	for (long long unsigned i = 0; i < l; ++i)
		res += ((a >> i) & 1) << (l - i - 1);
	return res;
}

vector<long long unsigned> fft (vector<long long unsigned> v0, bool rev = 0) {
	if (rev)
		reverse(r.begin() + 1, r.end());
	vector<long long unsigned> v = v0;
	for (long long unsigned i = 0; i < m; ++i)
		if (i < invert(i))
			swap(v[i], v[invert(i)]);
	for (long long unsigned i = 0, step = 1, power = m / 2; i < l; ++i, step *= 2, power /= 2)
		for (long long unsigned j = 0; j < m; j += 2 * step) 
			for (long long unsigned k = 0; k < step; ++k) {
				long long unsigned a = j + k, b = j + k + step;
				long long unsigned x = (v[a] + v[b] * 1ull * r[k * power]) % p, y = (v[a] + v[b] * 1ull * r[k * power + m / 2]) % p;
				v[a] = x; v[b] = y;
			}
	if (rev) {
		reverse(r.begin() + 1, r.end());
		for (long long unsigned i = 0; i < m; ++i)
			v[i] = (v[i] * 1ull * d) % p;
	}
	return v;
}

vector<long long unsigned> dot (vector<long long unsigned> v1, vector<long long unsigned> v2) {
	vector<long long unsigned> v(m);
	for (long long unsigned i = 0; i < m; ++i)
		v[i] = (v1[i] * 1ull * v2[i]) % p;
	return v;
}

int main() {
	freopen("input.txt", "r", stdin);
	build_r();
	long long unsigned o, k;
	string s, p;
	cin >> o >> k >> s >> p;
	vector<long long unsigned> v_s(m), v_p(m), c(m);
	vector<long long unsigned> w(m);
	for (long long unsigned i = 0; (i < p.size()) && (i < s.size()); ++i)
		w[p.size() - 1] += (s[i] == 'o') * o + (s[i] == 'k') * k;
	for (long long unsigned i = p.size(); i < s.size(); ++i)
		w[i] = w[i - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k - (s[i - p.size()] == 'o') * o - (s[i - p.size()] == 'k') * k;
	for (long long unsigned i = 0; i < s.size() ; ++i)
		v_s[i] = (s[i] == 'o');
	for (long long unsigned i = 0; i < p.size(); ++i)
		v_p[i] = (p[p.size() - i - 1] == 'o');
	v_s = fft(dot(fft(v_s), fft(v_p)), 1);
	for (long long unsigned i = 0; i < m; ++i)
		c[i] += v_s[i];
        for (long long unsigned i = 0; i < s.size() ; ++i)
                v_s[i] = (s[i] == 'k');
        for (long long unsigned i = 0; i < p.size(); ++i)
                v_p[i] = (p[p.size() - i - 1] == 'k');
        v_s = fft(dot(fft(v_s), fft(v_p)), 1);
        for (long long unsigned i = 0; i < m; ++i)
                c[i] += v_s[i];
	for (long long unsigned i = 0; i < s.size() ; ++i) 
                v_s[i] = 1;
        for (long long unsigned i = 0; i < p.size(); ++i)
                v_p[i] = (p[p.size() - i - 1] == '?');
        v_s = fft(dot(fft(v_s), fft(v_p)), 1);
        for (long long unsigned i = 0; i < m; ++i)
                c[i] += v_s[i];
	vector<long long unsigned> dp(m);
	dp[p.size() - 1] = w[p.size() - 1] / (p.size() - c[p.size() - 1] > 62 ? bin_pow(2, 62) : bin_pow(2, p.size() - c[p.size() - 1]));
	for (long long unsigned i = p.size(); i < s.size(); ++i) {
		if (i < 2 * p.size() - 1)
			dp[i] = max(dp[i - 1], w[i] / (p.size() - c[i] > 62 ? bin_pow(2, 62) : bin_pow(2, p.size() - c[i])));
		else
			dp[i] = max(dp[i - 1], w[i] / (p.size() - c[i] > 62 ? bin_pow(2, 62) : bin_pow(2, p.size() - c[i])) + dp[i - p.size()]);
	}
	cout << dp[s.size() - 1] << endl;
}



