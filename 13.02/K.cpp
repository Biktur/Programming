#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<algorithm>

using namespace std;

mt19937 rnd(time(0));

bool cmp(int a, int b) {
        if (a == b)
                return 1;
        cout << "? " << a << " " << b << endl;
        char c;
        cin >> c;
        return (c == '<');
}

void sift (vector<int>& v, int i, int k) {
        if (2 * i + 1 >= k)
                return;
        else if (2 * i + 2 >= k) {
                if (cmp(v[i], v[2 * i + 1]))
			swap(v[i], v[2 * i + 1]);
	}
	else {
		if (cmp(v[2 * i + 1], v[2 * i + 2])) {
			if (cmp(v[i], v[2 * i + 2])) {
				swap(v[i], v[2 * i + 2]);
				sift(v, 2 * i + 2, k);
			}
		}
		else {
			if (cmp(v[i], v[2 * i + 1])) {
                                swap(v[i], v[2 * i + 1]);
                                sift(v, 2 * i + 1, k);
                        }
		}
	}
}

void shift (vector<int>& v, int i) {
	if (i == 0)
		return;
	if (cmp(v[(i - 1) / 2], v[i])) {
		swap(v[i], v[(i - 1) / 2]);
		shift (v, (i - 1) / 2);
	}
}

int main() {
	int n, k;
	vector<int> v;
	cin >> n >> k;
	vector<int> p(n);
	for (int i = 0; i < n; ++i)
		p[i] = i + 1;
	shuffle(p.begin(), p.end(), rnd);
	for (int i = 0; i < n; ++i) {
		if (v.size() < k) { 
			v.push_back(p[i]);
			shift(v, v.size() - 1);
		}
		else
			if (cmp(p[i], v[0])) {
				v[0] = p[i];
				sift(v, 0, k);
			}
	}
	sort (v.begin(), v.end(), cmp);
	cout << "! ";
	for (int i = 0; i < k; ++i)
		cout << v[i] << " ";
	cout << endl;
}



