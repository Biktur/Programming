#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<int>> e(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			int l;
			cin >> l;
			e[i][j] = (l + 1 ? l : 1000000000);
		}
	vector<vector<int>> d = e;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k =  0; k < n; ++k)
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
	int r = 1000000000, diam = 0;
	for (int i = 0; i < n; ++i) {
		r = min(*max_element(d[i].begin(), d[i].end()), r);
		diam = max(*max_element(d[i].begin(), d[i].end()), diam);
	}
	cout << diam << endl << r << endl;
}	


