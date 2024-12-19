#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, long long>>> e(n);
	for (int i = 0; i < m; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		e[a - 1].push_back(make_pair(b - 1, w));
	}
	vector<long long> d(n, -1000000000);
	d[0] = 0;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < n; ++j)
			for (auto [k, w] : e[j])
				d[k] = max(d[k], w + d[j]);
	vector<long long> d0 = d;
	long long res = d[n - 1];
	for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                        for (auto [k, w] : e[j])
                                d[k] = max(d[k], w + d[j]);
	for (int i = 0; i < n; ++i)
		if (d0[i] > -900000000 && d[i] != d0[i])
			d[i] = 1000000000;
	for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                        for (auto [k, w] : e[j])
                                d[k] = max(d[k], w + d[j]);
	if (res <= -900000000)
		cout << ":(" << endl;
	else if (d[n - 1] != res)
                cout << ":)" << endl;
	else
		cout << res << endl;
}
