#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> e(n, vector<int>(n, 1000000000));
	for (int i = 0; i < n; ++i)
		e[i][i] = 0;
	for (int k = 0; k < m; ++k) {	
		int i, j, t;
		cin >> i >> j >> t;
		e[i - 1][j - 1] = min(e[i - 1][j - 1], t);
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k) {
				if (e[j][k] < -1000000000)
					continue;
				e[j][k] = min(e[j][i] + e[i][k], e[j][k]);
			}
	bool f = 1;
	for (int i = 0; i < n; ++i)
		if (e[i][i] < 0) {
			f = 0;
			break;
		}
	if (f) {
		vector<int> ans(n);
		for (int i = 0; i < n; ++i) {
			int l = 1000000000;
			for (int j = 0; j < n; ++j)
				l = min(l, e[i][j]);
			ans[i] = l;
			for (int j = 0; j < n; ++j) {
				e[i][j] -= l;
				e[j][i] += l;
			}
		}
		for (int i = 0; i < n; ++i)
			cout << ans[i] - ans[0] << endl;
	}
	else
		cout << "NO SOLUTION" << endl;
}
