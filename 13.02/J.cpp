#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<map>

using namespace std;

mt19937_64 rnd(463543);

int main() {
	ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
	vector<long long unsigned> v(3000000);
	map<long long unsigned, int> m;
	for (int i = 0; i < 1000000; ++i) {
		v[i] = rnd();
		m[v[i]] = i + 1;
	}
	string s;
	cin >> s;
	long long unsigned x = 0;
	if (s == "second")
		cin >> x;
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < k; ++i) {
		int a;
		cin >> a;
		x ^= v[a - 1];
	}
	if (s == "first")
		cout << x << endl;
	else {
		for (int i = 0; i < n; ++i)
			x ^= v[i];
		for (int i = 0; i < n; ++i)
			if (m[x ^ v[i]]) {
				cout << i + 1 << " " << m[x ^ v[i]] << endl;
				break;
			}
	}
}

