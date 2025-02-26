#include<iostream>
#include<vector>
#include<string>

using namespace std;

int p1 = 1e9 + 7, x1 = 137, p2 = 1e9 + 9, x2 = 239;

int main() {
	string t;
	cin >> t;
	if (t == "first") {
		int n;
		string s;
		cin >> n >> s;
		int h1 = 0, h2 = 0;
		for (int i = 0; i < n; ++i) {
			h1 = (h1 * 1ll * x1 + s[i]) % p1;
			h2 = (h2 * 1ll * x2 + s[i]) % p2;
		}
		cout << to_string(h1) + " " + to_string(h2);
	}
	else {
		int n, h1, h2;
		string s;
		cin >> n >> s >> h1 >> h2;
		int k1 = 0, k2 = 0, xn1 = 1, xn2 = 1;
		for (int i = 0; i < n; ++i) {
                        k1 = (k1 * 1ll * x1 + s[i]) % p1;
                        k2 = (k2 * 1ll * x2 + s[i]) % p2;
			xn1 = (xn1 * 1ll * x1) % p1;
			xn2 = (xn2 * 1ll * x2) % p2;
                }
		for (int i = 0; i < n; ++i) {
			if ((k1 == h1) && (k2 == h2)) {
				cout << "YES" << endl;
				return 0;
			}
			k1 = (k1 * 1ll * x1 - s[i] * 1ll * xn1 + s[i] + p1 * 1ll * p1) % p1;
			k2 = (k2 * 1ll * x2 - s[i] * 1ll * xn2 + s[i] + p2 * 1ll * p2) % p2;
		}
		cout << "NO" << endl;
	}
}
			
