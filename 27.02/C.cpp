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
	int n, k;
	cin >> n >> k;
	vector<unsigned> v(m);
	for (int i = 1; i < k; ++i)
		v[bin_p(i, k, n)]++;
	auto [p_p, p_q] = fft(dot(fft({v, v}), fft({v, v})), 1);
	long long s_p = 0, s_q = 0;
	for (int i = 0; i < m / 2; ++i) {
		s_p = (s_p + (((v[i] * 1ull * (v[i] - 1)) % p * 1ull * p_2 + v[i]) % p) * 1ull * v[(2 * i) % k]) % p, s_q = (s_q + (((v[i] * 1ull * (v[i] - 1)) % q * 1ull * q_2 + v[i]) % q) * 1ull * v[(2 * i) % k]) % q;
		p_p[2 * i] = (p_p[2 * i] + p - ((v[i] * 1ull * v[i]) % p)) % p, p_q[2 * i] = (p_q[2 * i] + q - ((v[i] * 1ull * v[i]) % q)) % q;
	}
	for (int i = 0; i < m; ++i)
		s_p = (s_p + ((p_p[i] * 1ull * p_2) % p) * 1ull * v[i % k]) % p , s_q = (s_q + ((p_q[i] * 1ull * q_2) % q) * 1ull * v[i % k]) % q;
	cout << crt(s_p, s_q) << endl;
}

