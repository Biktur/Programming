#include<iostream>
#include<random>
#include<ctime>
#include<algorithm>

using namespace std;

mt19937 rnd(time(0));

bool cmp (vector<int> a, vector<int> b) {
	return a[0] < b[0];
}

int main() {
	string s;
	cin >> s;
	if (s == "ask") {
		int n;
		cin >> n;
		cout << "1000 1000" << endl;
		for (int i = 0; i < 1000; ++i)
			cout << rnd() % n + 1 << " ";
	}
	else {
		int k, l;
		cin >> k >> l;
		vector<vector<int>> v(k, vector<int>(l));
		int a = 0, b = 1000;
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < l; ++j)
				cin >> v[i][j];
		sort (v.begin(), v.end(), cmp);
		for (int i = 0; i < k; ++i)
                        for (int j = 0; j < l; ++j)
                                if (v[i][j] == 1 && j < b)
                                        a = i, b = j;
		cout << 1 << " ";
		b++;
		while (v[a][b] != 1) {
			cout << v[a][b] << " ";
			int lb = 0, rb = k;
			while (lb + 1 < rb) {
				int m = (lb + rb) / 2;
				if (v[m][0] <= v[a][b])
					lb = m;
				else
					rb = m;
			}
			if (v[lb][0] == v[a][b])
				a = lb, b = 0;
			b++;
		}
	}
}


		
