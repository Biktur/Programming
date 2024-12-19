#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<vector<pair<int, long long>>> e(n);
	vector<int> p(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			int w;
			cin >> w;
			if (w != 100000)
				e[i].push_back(make_pair(j, w));
		}
	vector<long long> d(n, 1000000000);
	d[0] = 0;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < n; ++j)
			for (auto [k, w] : e[j])
				if (w + d[j] < d[k]) {
					d[k] = w + d[j];
					p[k] = j;
				}
	vector<long long> d0 = d;
	for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                        for (auto [k, w] : e[j])
                                if (w + d[j] < d[k]) {
                                        d[k] = w + d[j];
                                        p[k] = j;
                                }
	int a = -1;
	for (int i = 0; i < n; ++i)
		if (d[i] != d0[i]) {
			a = i;
			break;
		}
	cout << (a + 1 ? "YES" : "NO") << endl;
	if (a + 1) {
		vector<int> res = {a};
		int b = a;
		do {
			b = p[b];
			res.push_back(b);
			if (count(res.begin(), res.end(), b) == 2)
				break;
		}
		while (a != b);
		reverse(res.begin(), res.end());
		int l = find(res.begin() + 1, res.end(), res[0]) - res.begin();
		cout << l << endl;
		for (int i = 0; i < l; ++i)
			cout << res[i] + 1 << " ";
		cout << endl;
	}
}
