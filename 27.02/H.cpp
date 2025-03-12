#include<iostream>
#include<iomanip>
#include<vector>

using namespace std;

int main() {
	long long n, a, b, c, d, e, f, m;
	cin >> n >> a >> b >> c >> d >> e >> f >> m;
	cout << fixed << setprecision(4);
	for (int i = 0; i < m; ++i) {
		long long q;
		cin >> q;
		if (q != 0) {
			long double z_r1 = ((a + b * q) ^ (c * q)), z_i1 = ((d + e * q) ^ (f * q)), z_r2 = ((a + b * (n - q)) ^ (c * (n - q))), z_i2 = ((d + e * (n - q)) ^ (f * (n - q)));
			cout << (z_r1 + z_r2) / 2000 << " " << (z_i1 - z_i2) / 2000 << " " << (z_i1 + z_i2) / 2000 << " " << (z_r2 - z_r1) / 2000 << endl;
		}
		else {
			long double z_r = a, z_i = d;
			cout << z_r / 1000 << " " << (long double)0 << " " << z_i / 1000 << " " << (long double)0 << endl;
		}
	}
}
