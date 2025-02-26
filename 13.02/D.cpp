#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

mt19937 rnd(time(0));

int gcde(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0, y = 1;
		return b;
	}
	int r = gcde(b % a, a, y, x);
	x -= (b / a) * y;
	return r;
}

int main () {
	vector<pair<int, int>> v;
	for (int i = 0; i < 13; ++i) {
		int x = rnd() % (1000000007);
		int e = 0;
		for (int j = 0; j < i; ++j) {
			int m = v[j].second;
			for (int l = 0; l < i; ++l) {
				if (l != j) {
					int a = 0, b = 0;
					gcde((v[j].first - v[l].first + 1000000007) % 1000000007, 1000000007, a, b);
					m = ((m * 1ll * (a + 1000000007)) % (1000000007) * 1ll  * (x - v[l].first + 1000000007)) % (1000000007);
				}
			}
			e = (e + m) % 1000000007;
		}
		cout << "ask " << x << endl;
		int r;
		cin >> r;
		if (r == e) {
			cout << "degree " << i - 1 << endl;
			return 0;
		}
		v.push_back({x, r});
	}
}
	


