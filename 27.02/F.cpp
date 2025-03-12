#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

const unsigned p = 167772161;

unsigned bin_pow(unsigned q, unsigned k) {
        if (k == 0)
                return 1;
        return (bin_pow((q * 1ull * q) % p, k / 2) * 1ull * (k % 2 ? q : 1)) % p;
}

int l = 18;
int m = 262144;
unsigned d = bin_pow(unsigned(m), p - 2);
unsigned x = bin_pow(3, 5 << (25 - l));
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

int main() {
	ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
	build_r();
	long long unsigned o, k;
	string s, p;
	cin >> o >> k >> s >> p;
	vector<unsigned> v_s(m), v_p(m), c(m);
	vector<long long> w(m);
	for (int i = 0; (i < p.size()) && (i < s.size()); ++i)
		w[p.size() - 1] += (s[i] == 'o') * o + (s[i] == 'k') * k;
	for (int i = p.size(); i < s.size(); ++i)
		w[i] = w[i - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k - (s[i - p.size()] == 'o') * o - (s[i - p.size()] == 'k') * k;
	for (int i = 0; i < s.size() ; ++i)
		v_s[i] = (s[i] == 'o');
	for (int i = 0; i < p.size(); ++i)
		v_p[i] = (p[p.size() - i - 1] == 'o');
	v_s = fft(dot(fft(v_s), fft(v_p)), 1);
	for (int i = 0; i < m; ++i)
		c[i] += v_s[i];
        for (int i = 0; i < s.size() ; ++i)
                v_s[i] = (s[i] == 'k');
        for (int i = 0; i < p.size(); ++i)
                v_p[i] = (p[p.size() - i - 1] == 'k');
        v_s = fft(dot(fft(v_s), fft(v_p)), 1);
        for (int i = 0; i < m; ++i)
                c[i] += v_s[i];
	for (int i = 0; i < s.size() ; ++i) 
                v_s[i] = 1;
        for (int i = 0; i < p.size(); ++i)
                v_p[i] = (p[p.size() - i - 1] == '?');
        v_s = fft(dot(fft(v_s), fft(v_p)), 1);
	for (int i = 0; i < m; ++i)
                c[i] += v_s[i];
	vector<long long> dp(m);
	dp[p.size() - 1] = (w[p.size() - 1] >> (p.size() - c[p.size() - 1]));
	for (int i = p.size(); i < s.size(); ++i) {
		if (i < 2 * p.size() - 1)
			dp[i] = max(dp[i - 1], (w[i] >> (p.size() - c[i])));
		else
			dp[i] = max(dp[i - 1], (w[i] >> (p.size() - c[i])) + dp[i - p.size()]);
	}
	cout << dp[s.size() - 1] << endl;
}

