#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.first < b.first;
}

int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> v(n), p(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		v[i] = {x, y};
		p[i] = {y, x};
	}
	sort(v.begin(), v.end());
	sort(p.begin(), p.end());
	long long m = 0;
	for (auto i : v) {
		auto r1 = equal_range(v.begin(), v.end(), i, cmp), r2 = equal_range(p.begin(), p.end(), make_pair(i.second, i.first), cmp);
		for (auto j = r1.first; j < r1.second; ++j)
			for (auto k = r2.first; k < r2.second; ++k)
				if (binary_search(v.begin(), v.end(), make_pair(k->second, j->second)))
					m = max(m, abs(i.first - k->second) * 1ll * abs(i.second - j->second));
	}
	cout << m << endl;
}
