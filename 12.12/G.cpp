#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<algorithm>
#include<numeric>
#include<cmath>

using namespace std;

struct Dsu {
        int n;
        vector<int> v;
        vector<int> r;
        Dsu(int n1) {
                n = n1;
                v = vector<int>(n);
                r = vector<int>(n);
                for (int j = 0; j < n; ++j)
                        v[j] = j;
        }
        int root (int a) {
                if (v[a] == a)
                        return a;
                return root(v[a]);
        }
        bool unite (int a, int b) {
                a = root(a), b = root(b);
                if (a == b)
                        return 0;
                if (r[a] > r[b])
                        swap(a, b);
                v[a] = b;
                r[b] += (r[a] == r[b]);
                return 1;
        }
};

struct Triple {
	int l, a, b;
	Triple (int l1 = 0, int a1 = 0, int b1 = 0) {
		l = l1, a = a1, b = b1;
	}
};

bool operator < (Triple a, Triple b) {
	return a.l < b.l;
}

int main() {
	int n, k;
	cin >> n >> k;
	Dsu G(n);
	vector<pair<int, int>> v(n);
	vector<Triple> d;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		v[i] = make_pair(x, y);
		for (int j = 0; j < i; ++j)
			d.push_back(Triple((x - v[j].first) * (x - v[j].first) + (y - v[j].second) * (y - v[j].second), i, j));
	}
	sort(d.begin(), d.end());
	if (n == k)
		cout << 0 << endl;
	else {
		int c = n;
		for (auto [l, a, b] : d) {
			c -= G.unite(a, b);
			if (c == k) {
				cout << setprecision(6) << fixed << sqrt(l) << endl;
				break;
			}
		}
	}
	map<int, int> r;
	for (int i = 0; i < n; ++i) {
		if (r.count(G.root(i)) == 0)
			r[G.root(i)] = r.size() + 1;
		cout << r[G.root(i)] << " ";
	}
	cout << endl;
}
