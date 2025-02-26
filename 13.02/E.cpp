
#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<map>

using namespace std;

mt19937_64 rnd(time(0));

int main() {
	ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<long long unsigned> v(1000000);
	vector<long long unsigned> h(n + m);
	map<long long unsigned, int> s;
	for (int i = 0; i < 1000000; ++i)
		v[i] =  rnd();
	for (int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j) {
			int a;
			cin >> a;
			h[i] ^= v[a - 1];
		}
		s[h[i]]++;
	}
	for (int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		h[n + i] = h[x - 1] ^ h[y - 1];
		cout << s[h[n + i]] << " ";
		s[h[n + i]]++;
	}
}


