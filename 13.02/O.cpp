#include<iostream>
#include<random>
#include<ctime>

using namespace std;

mt19937 rnd(time(0));

bool solve(int n, int la, int ra, int lb, int rb, bool f = 1, int m = 1) {
	if (ra >= lb)
		return f ^ 1;
	if (f) {
		if (la - m < 1)
			return solve(n, la, ra + m, lb, rb, f ^ 1, m);
		else if (ra + m > n)
			return solve(n, la - m, ra, lb, rb, f ^ 1, m);
		else 
			return solve(n, la, ra + m, lb, rb, f ^ 1, m) || solve(n, la - m, ra, lb, rb, f ^ 1, m);
	}
	else {
		if (lb - m < 1)
                        return solve(n, la, ra, lb, rb + m, f ^ 1, m * 2);
                else if (rb + m > n)
                        return solve(n, la, ra, lb - m, rb, f ^ 1, m * 2);
                else
                        return solve(n, la, ra, lb - m, rb, f ^ 1, m * 2) && solve(n, la, ra, lb, rb + m, f ^ 1, m * 2);
        }
}

int main() {
	int n, x, y;
	cin >> n >> x >> y;
	cout << (solve(n, x, x, y, y) ? "letoucan" : "cdkrot") << endl;
}
