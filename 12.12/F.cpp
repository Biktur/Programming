#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

int main() {
        int n;
        cin >> n;
        vector<vector<int>> e(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                        cin >> e[i][j];
        vector<vector<int>> d = e;
        for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                        for (int k =  0; k < n; ++k)
				if (d[j][i] + 1 && d[i][k] + 1 && (d[j][i] + d[i][k] < d[j][k] || d[j][k] == -1))
                                	d[j][k] = d[j][i] + d[i][k];
        int diam = 0;
        for (int i = 0; i < n; ++i)
                diam = max(*max_element(d[i].begin(), d[i].end()), diam);
        cout << diam << endl;
}
