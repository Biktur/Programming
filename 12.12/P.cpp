#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	vector<vector<pair<int, int>>> e(n);
	for (int i = 0; i < m; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		e[a - 1].push_back(make_pair(b - 1, w));
		e[b - 1].push_back(make_pair(a - 1, w));
	}
	vector<int> d(n, 1000000000);
	vector<bool> f(n);
	set<pair<int, int>> p;
	int u = s - 1;
	d[u] = 0;
	p.insert(make_pair(0, u));
	while (!p.empty()) {
		u = p.begin()->second;
		p.erase(p.begin());
		f[u] = 1;
		for (auto [i, l] : e[u])
			if (!f[i] && d[u] + l < d[i]) {
				p.erase(make_pair(d[i], i));
				d[i] = d[u] + l;
				p.insert(make_pair(d[i], i));
			}
	}
	cout << (d[t - 1] == 1000000000 ? -1 : d[t - 1]) << endl;
}
