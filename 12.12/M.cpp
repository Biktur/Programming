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
	int n, m;
	cin >> n >> m;
	Dsu G(n);
	vector<Triple> e;
	for (int i = 0; i < m; ++i) {
		int a, b, l;
		cin >> a >> b >> l;
		e.push_back(Triple(l, a - 1, b - 1));
	}
	sort(e.begin(), e.end());
	int k = n;
	long long res = 0;
	for (auto [l, a, b] : e) {
		bool f = G.unite(a, b);
		k -= f;
		if (l < 0 || f)
			res += l;
	}
	if (k - 1)
		cout << "Impossible" << endl;
	else
		cout << res << endl;
}
