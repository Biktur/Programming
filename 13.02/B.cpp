#include<iostream>

using namespace std;

int main() {
	unsigned a, c, s;
	cin >> a >> c >> s;
	for (int i = 0; i < 10; ++i) {
		s = s * a + c;
		cout << s << " ";
	}
}
