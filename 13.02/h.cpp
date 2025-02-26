#include<iostream>
#include<vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	int l = -1, r = n;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (m == n - 1) {
			r = m;
			continue;
		}
		cout << "? " << m + 1 << endl << "? " << m + 2 * (1 - m % 2) << endl;
		int a, b;
		cin >> a >> b;
		if (a == b)
			l = m;
		else
			r = m;
	}
	cout << "? " << l + (l + 2) % 2 + 1 << endl;
	int a;
	cin >> a;
	cout << "! " << a << endl;
}
