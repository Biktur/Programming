#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> e(n);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		e[a - 1].push_back(b - 1);
		e[b - 1].push_back(a - 1);
	}
	long long s = 0;
	for (int i = 0; i < n; ++i) {
		vector<int> d(n,  100000);
		queue<int> q;
		d[i] = 0;
		q.push(i);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int i : e[v])
				if (d[i] == 100000) {
					d[i] = d[v] + 1;
					s += d[i];
					q.push(i);
				}
		}
	}
	cout << s / 2 << endl;
}
