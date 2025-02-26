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
	vector<long long unsigned> v(1000000);
	map<long long unsigned, int> m;
	for (int i = 0; i < 1000000; ++i) {
		v[i] = rnd();
		m[v[i]] = i + 1;
	}
	long long unsigned x = 0;
	string s;
	cin >> s;
	if (s == "resume")
		cin >> x;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		x ^= v[a - 1];
		if (x == 0)
			cout << 0 << endl;
		else if (m[x])
			cout << m[x] << endl;
		else
			cout << -1 << endl;
	}
	if (s == "start")
		cout << x << endl;
}

