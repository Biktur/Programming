#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
	vector<int> p(3);
	for (int i = 0; i < 3; ++i) {
		char c;
		cin >> c;
		p[i] = c - 'i';
	}
	if (p[0] == 2)
		cout << "0 0" << endl;
	else if (p[1] == 2)
		cout << "4 3\n1 3\n2 3\n2 4" << endl;
	else
		cout << "4 3\n1 3\n2 4\n3 4" << endl;
}
