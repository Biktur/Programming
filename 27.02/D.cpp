
#include<iostream>
#include<iomanip>
#include<vector>
#include<complex>
#include<algorithm>
#include<cmath>

const double pi = acos(-1.0);

using namespace std;

int invert (int a, int s) {
        int res = 0;
        for (int i = 0; i < s; ++i)
                res += ((a >> i) & 1) << (s - i - 1);
        return res;
}

unsigned bin_pow(unsigned q, unsigned k) {
        if (k == 0)
                return 1;
        return bin_pow(q * q, k / 2) * (k % 2 ? q : 1);
}

int main() {
	ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
	int s, t;
	cin >> s >> t;
	unsigned n = bin_pow(2, s);
	vector<complex<double>> v(n);
	for (int i = 0; i < n; ++i) {
		double a, b;
		cin >> a >> b;
		v[i] = {a, b};
	}
	vector<complex<double>> r(n);
	for (int i = 0; i < n; ++i)
		r[i] = {cos(i * 2 * pi / n), sin(i * 2 * pi / n)};
	for (int i = 0; i < n; ++i)
                if (i < invert(i, s))
                        swap(v[i], v[invert(i, s)]);
	for (int i = 0, step = n / 2; i < t; ++i, step /= 2) {
		vector<complex<double>> p(n);
                for (int j = 0; j < n; j += step)
                        for (int k = 0; k < step; k += 1) {
				int u = ((j + k) * 2) % n;
				p[j + k] = v[u] + v[u + 1] * r[j];
			}
		v = p;
	}
	for (int i = 0; i < n; ++i)
		cout << fixed << setprecision(8) << v[i].real() << " " << v[i].imag() << endl;
}


