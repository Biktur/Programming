#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n, s, fin;
	cin >> n >> s >> fin;
	vector<vector<int>> e(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			int l;
			cin >> l;
			e[i][j] = (l + 1 ? l : 1000000000);
		}
	vector<int> d(n, 1000000000);
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
	cout << (d[fin - 1] == 1000000000 ? -1 : d[fin - 1]) << endl;
}
