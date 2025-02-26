#include<iostream>
#include<random>
#include<ctime>

using namespace std;

mt19937 rnd(time(0));

int main() {
	bool f = 1;
	for (int i = 0; i < 30000; ++i) {
		if (f) {
			cout << 1 << endl;
			string resp;
			cin >> resp;
			if (resp == "yes")
				return 0;
			f = 0;
		}
		else {
			cout << rnd() << endl;
                        string resp;
                        cin >> resp;
			if (resp == "yes")
                                f = 1;
		}
	}
}

