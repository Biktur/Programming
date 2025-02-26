#include<iostream>
#include<vector>
#include<random>

using namespace std;

mt19937 rnd(time(0));

int main () {
	int n;
	cin >> n;
	for (int i = 0; i < 100; ++i) {
		cout << rnd() % (2 * n) + 1 << endl;
		char c;
		cin >> c;
		if (c == 'a')
			return 0;
	}
}
