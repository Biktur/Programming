#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int n, m, k;
vector<vector<pair<int, int>>> e;
vector<int> s;
vector<vector<bool>> f;
vector<vector<int>> p;

bool dfs (int v, int l, int a) {
       	if (l == k) {
                p[v][l] = a;
                return 1;
        }
	if (f[v][l])
             	return 0;
     	f[v][l] = 1;
        p[v][l] = a;
     	for (auto [u, w] : e[v])
              	if (w == s[l] && dfs(u, l + 1, v)) 
                        return 1;
   	return 0;
}

int main() {
	cin >> n >> m >> k;
	e = vector<vector<pair<int, int>>>(n);
	for (int i = 0; i < m; ++i) {
		int u, v, l;
		cin >> u >> v >> l;
		e[u - 1].push_back(make_pair(v - 1, l));
		e[v - 1].push_back(make_pair(u - 1, l));
	}
	for (int i = 0; i < n; ++i)
		sort(e[i].begin(), e[i].end());
	s = vector<int>(k);
	for (int i = 0; i < k; ++i)
	       cin >> s[i];
	f = vector<vector<bool>>(n, vector<bool>(k + 1));
	p = vector<vector<int>>(n, vector<int>(k + 1, -1));
	for (int i = 0; i < n; ++i)
		if (dfs(i, 0, -1))
			for (int j = 0; j < n; ++j)
				if (p[j][k] + 1) {
					int a = j;
					vector<int> ans(k + 1);
					for (int l = k; l >= 0; --l) {
						ans[l] = a + 1;
						a = p[a][l];
					}
					for (int i : ans)
						cout << i << " ";
					cout << endl;
					return 0;
				}
	cout << "No solution" << endl;
}

