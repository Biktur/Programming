#include<iostream>

using namespace std;

int main() {
	freopen("input.txt", "w", stdout), freopen("output.txt", "r", stdin);
	cout << "5000 5000" << endl;
	for (int i = 0; i < 250000; ++i)
		cout << 'o';
	cout << endl;
	for (int i = 0; i < 250000; ++i)
                cout << 'o';
        cout << endl;
}
