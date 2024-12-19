#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<numeric>
#include<cmath>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> v(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		v[i] = make_pair(x, y);
	}
	vector<long double> d(n, 2000000000);
	vector<int> p(n);
	vector<pair<int, int>> ans;
	vector<bool> f(n);
	int u = 0;
	d[u] = 0;
	p[u] = -1;
	long double l = 0;
	while (u != -1) {
		if (u != 0)
			ans.push_back(make_pair(u + 1, p[u] + 1));
		l += sqrt(d[u]);
		f[u] = 1;
		for (int i = 0; i < n; ++i)
			if (i != u && (v[i].first - v[u].first) * (v[i].first - v[u].first) + (v[i].second - v[u].second) * (v[i].second - v[u].second) < d[i]) {
				d[i] = (v[i].first - v[u].first) * (v[i].first - v[u].first) + (v[i].second - v[u].second) * (v[i].second - v[u].second);
				p[i] = u;
			}
		u = -1;
		for (int i = 0; i < n; ++i)
			if (!f[i] && (u == -1 || d[i] < d[u]))
				u = i;
	}
	cout << setprecision(16) << l << endl;
	cout << n - 1 << endl;	
	sort(ans.begin(), ans.end());
	for (int i = 0; i < n - 1; ++i)
		if (ans[i].second < ans[i].first)
			swap(ans[i].first, ans[i].second);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < n - 1; ++i)
		cout << ans[i].first << " " << ans[i].second << endl;
}
