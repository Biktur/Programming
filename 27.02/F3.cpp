
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

const unsigned p = 998244353;
const unsigned q = 167772161;

unsigned bin_pow_p(unsigned a, unsigned k) {
        if (k == 0)
                return 1;
        return (bin_pow_p((a * 1ull * a) % p, k / 2) * 1ull * (k % 2 ? a : 1)) % p;
}

unsigned bin_pow_q(unsigned a, unsigned k) {
        if (k == 0)
                return 1;
        return (bin_pow_q((a * 1ull * a) % q, k / 2) * 1ull * (k % 2 ? a : 1)) % q;
}

unsigned bin_p(unsigned q, unsigned p, unsigned k) {
        if (k == 0)
                return 1;
        return (bin_p((q * 1ull * q) % p, p, k / 2) * 1ull * (k % 2 ? q : 1)) % p;
}

int l = 21;
int m = 2097152;
unsigned d_p = bin_pow_p(unsigned(m), p - 2), d_q = bin_pow_q(unsigned(m), q - 2);
unsigned x_p = bin_pow_p(3, 119 << (23 - l)), x_q = bin_pow_q(3, 5 << (25 - l));
unsigned p_2 = bin_pow_p(2, p - 2), q_2 = bin_pow_q(2, q - 2);

vector<unsigned> r_p(m), r_q(m);

void build_r() {
	int t_p = 1, t_q = 1;
	for (int i = 0; i < m; ++i, t_p = (t_p * 1ull * x_p) % p, t_q = (t_q * 1ull * x_q) % q) {
        	r_p[i] = t_p;
		r_q[i] = t_q;
	}
}

int invert (int a) {
	int res = 0;
	for (int i = 0; i < l; ++i)
		res += ((a >> i) & 1) << (l - i - 1);
	return res;
}

pair<vector<unsigned>, vector<unsigned>> fft (pair<vector<unsigned>, vector<unsigned>> v0, bool rev = 0) {
	if (rev) 
		reverse(r_p.begin() + 1, r_p.end()), reverse(r_q.begin() + 1, r_q.end());
	vector<unsigned> v_p = v0.first, v_q = v0.second;
	for (int i = 0; i < m; ++i)
		if (i < invert(i))
			swap(v_p[i], v_p[invert(i)]), swap(v_q[i], v_q[invert(i)]);
	for (int i = 0, step = 1, power = m / 2; i < l; ++i, step *= 2, power /= 2)
		for (int j = 0; j < m; j += 2 * step) 
			for (int k = 0; k < step; ++k) {
				int a = j + k, b = j + k + step;
				unsigned x_p = (v_p[a] + v_p[b] * 1ull * r_p[k * power]) % p, y_p = (v_p[a] + v_p[b] * 1ull * r_p[k * power + m / 2]) % p, x_q = (v_q[a] + v_q[b] * 1ull * r_q[k * power]) % q, y_q = (v_q[a] + v_q[b] * 1ull * r_q[k * power + m / 2]) % q;
				v_p[a] = x_p; v_p[b] = y_p, v_q[a] = x_q; v_q[b] = y_q;
			}
	if (rev) {
		reverse(r_p.begin() + 1, r_p.end()), reverse(r_q.begin() + 1, r_q.end());
		for (int i = 0; i < m; ++i)
			v_p[i] = (v_p[i] * 1ull * d_p) % p, v_q[i] = (v_q[i] * 1ull * d_q) % q;
	}
	return {v_p, v_q};
}

pair<vector<unsigned>, vector<unsigned>> dot (pair<vector<unsigned>, vector<unsigned>> v1, pair<vector<unsigned>, vector<unsigned>> v2) {
	vector<unsigned> v_p(m), v_q(m);
	for (int i = 0; i < m; ++i)
		v_p[i] = (v1.first[i] * 1ull * v2.first[i]) % p, v_q[i] = (v1.second[i] * 1ull * v2.second[i]) % q;
	return {v_p, v_q};
}

long long gcde(long long a, long long b, long long& x, long long& y) {
        if (a == 0) {
                x = 0, y = 1;
                return b;
        }
        long long r = gcde(b % a, a, y, x);
        x -= (b / a) * y;
        return r;
}

long long crt(long long a, long long b) {
	long long x, y;
	gcde(p, q, x, y);
	return (((y * a) % p) * 1ll * q + ((x * b) % q) * 1ll * p + p * 1ll * q * 2) % (p * 1ll * q);
}

int main() {
	build_r();
	int o, k;
	string s, t;
	cin >> o >> k >> s >> t;
	vector<unsigned> v_p(m), v_q(m), l_p(m), l_q(m), s_p(m), s_q(m), w_p(m), w_q(m);
	for (long long i = 0; i < t.size(); ++i)
                w_p[t.size() - 1] = (w_p[t.size() - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k) % p, w_q[t.size() - 1] = (w_q[t.size() - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k) % q;
        for (long long i = t.size(); i < s.size(); ++i)
                w_p[i] = (w_p[i - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k - (s[i - t.size()] == 'o') * o - (s[i - t.size()] == 'k') * k) % p, w_q[i] = (w_q[i - 1] + (s[i] == 'o') * o + (s[i] == 'k') * k - (s[i - t.size()] == 'o') * o - (s[i - t.size()] == 'k') * k) % q;
        for (long long i = 0; i < s.size(); ++i)
                v_p[i] = (s[i] == 'o'), v_q[i] = (s[i] == 'o');
        for (long long i = 0; i < t.size(); ++i)
                l_p[i] = (t[t.size() - i - 1] == 'o') + (t[t.size() - i - 1] == '?'), l_q[i] = (t[t.size() - i - 1] == 'o') + (t[t.size() - i - 1] == '?');
        [v_p, v_q] = fft(dot(fft({v_p, v_q}), fft({l_p, l_q})), 1);
        for (long long i = 0; i < s.size(); ++i)
                c_p[i] = (c_p[i] + v_p[i]) % p, c_q[i] = (c_q[i] + v_q[i]) % q; 
        for (long long i = 0; i < s.size(); ++i)
        	v_p[i] = (s[i] == 'k'), v_q[i] = (s[i] == 'k');
	for (long long i = 0; i < t.size(); ++i)
        	l_p[i] = (t[t.size() - i - 1] == 'k') + (t[t.size() - i - 1] == '?'), l_q[i] = (t[t.size() - i - 1] == 'k') + (t[t.size() - i - 1] == '?')
        [v_p, v_q] = fft(dot(fft({v_p, v_q}), fft({l_p, l_q})), 1);
	for (long long i = 0; i < s.size(); ++i)
		c_p[i] = (c_p[i] + v_p[i]) % p, c_q[i] = (c_q[i] + v_q[i]) % q;
	vector<unsigned> dp_p(m), dp_q(m);
	dp_p[t.size() - 1] = 
