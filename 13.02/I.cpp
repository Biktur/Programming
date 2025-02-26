#include<iostream>

using namespace std;

int main() {
	int lb = 1, rb = 1000000001;
	for (int i = 0; i < 100; ++i) {
		int a;
		cin >> a;
		if (a < lb)
			cout << ">" << endl;
		else if (a >= rb)
			cout << "<" << endl;
		else if (rb == lb + 1) {
			cout << "=" << endl;
			return 0;
		}
		else {
			if (a - lb >= rb - a - 1) { 
				rb = a;
				cout << "<" << endl;
			}
			else {
				lb = a + 1;
				cout << ">" << endl;
			}
		}
	}
}

