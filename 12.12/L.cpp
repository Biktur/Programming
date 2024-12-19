#include<iostream>
#include<iomanip>
#include<vector>
#include<set>
#include<algorithm>
#include<numeric>
#include<cmath>

using namespace std;

struct Triple {
	int x, y, i;
	Triple(int x1 = 0, int y1 = 0, int i1 = 0) {
		x = x1, y = y1, i = i1;
	}
};

bool operator < (Triple a, Triple b) {
	return a.x < b.x;
}

int main() {
	int n;
	cin >> n;
	vector<Triple> v(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		v[i] = Triple(x, y, i + 1);
	}
	sort (v.begin(), v.end());
	vector<long long> d(n, 2 * 1000000000000000000);
	vector<int> p(n);
	vector<pair<int, int>> ans;
	vector<bool> f(n);
	set<pair<int, int>> s;
	int u = 0;
	d[u] = 0;
	p[u] = -1;
	long double l = 0;
	s.insert(make_pair(0, 0));
	while (!s.empty()) {
		u = s.begin()->second;
		s.erase(s.begin());
		if (u != 0)
			ans.push_back(make_pair(v[u].i, v[p[u]].i));
		l += sqrt(d[u]);
		f[u] = 1;
		for (int i = max(0, u - 500); i < min(n, u + 501); ++i)
			if ((v[i].x - v[u].x) * (v[i].x - v[u].x) + (v[i].y - v[u].y) * (v[i].y - v[u].y) < d[i]) {
				if (!f[i])
					s.erase(make_pair(d[i], i));
				d[i] = (v[i].x - v[u].x) * (v[i].x - v[u].x) + (v[i].y - v[u].y) * (v[i].y - v[u].y);
				if (!f[i])
					s.insert(make_pair(d[i], i));
				p[i] = u;
			}
	}
	cout << setprecision(16) << l << endl;
	for (auto [a, b] : ans)
		cout << a << " " << b << endl;
}
