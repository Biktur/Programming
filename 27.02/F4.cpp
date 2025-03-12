
#include<iostream> #include<vector> #include<algorithm> #include<set>

using namespace std;

const unsigned p = 998244353;

unsigned bin_pow(unsigned q, unsigned k) { if (k == 0) return 1; return
	(bin_pow((q * 1ull * q) % p, k / 2) * 1ull * (k % 2 ? q : 1)) % p; }

	unsigned l = 18; unsigned m = 262144; unsigned d =
	bin_pow((unsigned)(m), p - 2); unsigned x = bin_pow(3, 119 * (1 << (23
					- l))); vector<unsigned> r(m);

	void build_r() { unsigned t = 1; for (int i = 0; i < m; ++i, t = (t *
				1ull * x) % p) r[i] = t; }

	int invert (unsigned a) { unsigned res = 0; for (int i = 0; i < l; ++i)
		res += ((a >> i) & 1) << (l - i - 1); return res; }

		vector<unsigned> fft (vector<unsigned> v0, bool rev = 0) { if
			(rev) reverse(r.begin() + 1, r.end()); vector<unsigned>
				v = v0; for (int i = 0; i < m; ++i) if (i <
						invert(i)) swap(v[i],
						v[invert(i)]); for (int i = 0,
						step = 1, power = m / 2; i < l;
						++i, step *= 2, power /= 2) for
							(unsigned j = 0; j < m;
							 j += 2 * step) for
							(unsigned k = 0; k <
							 step; ++k) { unsigned
								a = j + k, b =
									j + k +
									step;
								unsigned x =
									(v[a] +
									 v[b] *
									 1ull *
									 r[k *
									 power])
									% p, y
									= (v[a]
											+
											v[b]
											*
											1ull
											*
											r[k
											*
											power
											+
											m
											/
											2])
									% p;
								v[a] = x; v[b]
									= y; }
			if (rev) { reverse(r.begin() + 1, r.end()); for (int i
					= 0; i < m; ++i) v[i] = (v[i] * 1ull *
						d) % p; } return v; }

					vector<unsigned> dot (vector<unsigned>
							v1, vector<unsigned>
							v2) { vector<unsigned>
						v(m); for (int i = 0; i < m;
								++i) v[i] =
							(v1[i] * 1ull * v2[i])
							% p; return v; }

							unsigned unsigned
							bin_p(unsigned unsigned
									q,
									unsigned
									unsigned
									k) { if
								(k == 0) return
									1;
								return (bin_p(q
											*
											q,
											k
											/
											2)
										*
										(k
										 %
										 2
										 ?
										 q
										 :
										 1));
							}

int main() { build_r(); unsigned o, k; string s, p; cin >> o >> k >> s >> p;
	vector<unsigned> v(m), t(m), c(m), w(m); for (int i = 0; i < p.size();
			++i) w[p.size() - 1] += (s[i] == 'o') * o + (s[i] ==
				'k') * k; for (int i = p.size(); i < s.size();
					++i) w[i] = w[i - 1] + (s[i] == 'o') *
				o + (s[i] == 'k') * k - (s[i - p.size()] ==
						'o') * o - (s[i - p.size()] ==
							'k') * k; for (int i =
								0; i <
								s.size(); ++i)
							v[i] = (s[i] == 'o');
	for (int i = 0; i < p.size(); ++i) t[i] = (p[p.size() - i - 1] == 'o')
		+ (p[p.size() - i - 1] == '?'); v = fft(dot(fft(v), fft(t)),
				1); for (int i = 0; i < s.size(); ++i) c[i] +=
			v[i]; for (int i = 0; i < s.size(); ++i/
                v[i] = (s[i] == 'k');
        for (int i = 0; i < p.size(); ++i)
                t[i] = (p[p.size() - i - 1] == 'k') + (p[p.size() - i - 1] == '?');
        v = fft(dot(fft(v), fft(t)), 1);
        for (int i = 0; i < s.size(); ++i)
                c[i] += v[i];
	vector<unsigned> dp(m);
	dp[p.size() - 1] = w[p.size() - 1] / bin_p(2, min(31 (p.size() - c[p.size() - 1]));
	for (int i = p.size(); i < s.size(); ++i) {
		if (i < p.size() * 2 - 1)
			dp[i] = max(dp[i - 1], 1ll * (w[i] >> (p.size() - c[i])));
		else
			dp[i] = max(dp[i - 1], 1ll * (w[i] >> (p.size() - c[i])) + dp[i - p.size()]);
	}
	cout << dp[s.size() - 1] << endl;
}



