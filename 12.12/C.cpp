#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<numeric>
#include<cmath>

using namespace std;

int main() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	vector<vector<long double>> e(n, vector<long double>(n, 1000000000));
	for (int i = 0; i < m; ++i) {
		int a, b;
		long double l;
		cin >> a >> b >> l;
		e[a - 1][b - 1] = -log2((100 - l) / 100);
		e[b - 1][a - 1] = -log2((100 - l) / 100);
	}
	vector<long double> d(n, 1000000000);
	vector<bool> f(n);
	int u = s - 1;
	d[s - 1] = 0;
	while (u != -1) {
		f[u] = 1;
		for (int i = 0; i < n; ++i)
			d[i] = min(d[u] + e[u][i], d[i]);
		u = -1;
		for (int i = 0; i < n; ++i)
			if (!f[i] && (u == -1 || d[i] < d[u]))
				u = i;
	}
	cout << setprecision(6) << fixed << 1 - pow(2, -d[t - 1]) << endl;
}
