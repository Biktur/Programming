#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<int>> d(n, vector<int>(n));
	vector<vector<int>> p(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			p[i][j] = j;
			int w;
			cin >> w;
			if (w != 1e5)
				d[i][j] = w;
			else
				d[i][j] = 1e9;
			if (i == j && d[i][j] < 0) {
				cout << "YES" << endl << 1 << endl << i + 1 << endl;
				return 0;
			}
		}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				if (d[j][i] + d[i][k] < d[j][k]) {
					d[j][k] = d[j][i] + d[i][k];
					p[j][k] = p[j][i];
				}
	int a = -1, b = -1;
	for (int i = 0; i < n; ++i)
		if (d[i][i] < 0) {
			a = i, b = i;
			break;
		}
	if (a + 1) {
		cout << "YES" << endl;
		int l = 0;
		vector<int> res;
		do {
			res.push_back(a);
			a = p[a][b];
			l++;
		}
		while (a != b && l <= n);
		cout << l << endl;
		for (int i : res)
			cout << i + 1 << " ";
		cout << endl;
	}
	else 
		cout << "NO" << endl;
}
