#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<algorithm>

using namespace std;

mt19937 rnd(time(0));

bool cmp (int a, int b) {
	if (a == b)
		return 1;
	cout << "? " << a << " " << b << endl;
	char c;
	cin >> c;
	return (c == '<');
}

void fix_up (vector<int>& p, int i) {
	if (i == 0)
		return;
	if (cmp(p[(i - 1) / 2], p[i])) {
		swap(p[(i - 1) / 2], p[i]);
		fix_up(p, (i - 1) / 2);
	}
}

void fix_down (vector<int>& p, int n, int i) {
	if (2 * i + 1 >= n) {
		return;
	}
	else if (2 * i + 2 >= n) {
		if (cmp(p[i], p[2 * i + 1]))
			swap (p[i], p[2 * i + 1]);
	}
	else {
		if (cmp(p[2 * i + 1], p[2 * i + 2])) {
			if (cmp(p[i], p[2 * i + 2])) {
				swap(p[i], p[2 * i + 2]);
				fix_down(p, n, 2 * i + 2);
			}
		}
		else
			if (cmp(p[i], p[2 * i + 1])) {
				swap(p[i], p[2 * i + 1]);
				fix_down(p, n, 2 * i + 1);
			}
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		v[i] = i + 1;
	shuffle(v.begin(), v.end(), rnd);
	vector<int> p;
	for (int i = 0; i < n; ++i) {
		if (p.size() < k) {
			p.push_back(v[i]);
			fix_up(p, p.size() - 1);
		}
		else {
			if (cmp(v[i], p[0])) {
				p[0] = v[1];
				fix_down(p, k, 0);
			}
		}
	}
	sort(p.begin(), p.end(), cmp);
	cout << "! ";
	for (int i = 0; i < k; ++i)
		cout << p[i] << " ";
	cout << endl;
}


	
