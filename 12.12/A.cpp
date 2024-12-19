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
	for (int i = 0; i < m; ++i) {
		int a, b, l;
		cin >> a >> b >> l;
		e[a - 1][b - 1] = l;
	}
	vector<vector<int>> d = e;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k =  0; k < n; ++k)
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
	vector<int> ans(n);
	int k, l = 1000000000;
	for (int i = 0; i < n; ++i) {
		ans[i] = accumulate(d[i].begin(), d[i].end(), 0);
		if (l > ans[i]) {
			k = i + 1;
			l = ans[i];
		}
	}
	cout << k << " " << l << endl;
}	
