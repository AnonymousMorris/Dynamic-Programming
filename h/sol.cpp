#include<bits/stdc++.h>

using namespace std;

int main() {
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    for (int i = 0; i < r; i++) {
        cin >> grid[i];
    }

    int dp[r][c];
    dp[0][0] = 1;
    for (int j = 1; j < c; j++) {
        if (grid[0][j] == '#') {
            dp[0][j] = 0;
        }
        else {
            dp[0][j] = dp[0][j-1];
        }
    }

    for (int i = 1; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '#') {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = dp[i-1][j];
            if (j > 0) {
                dp[i][j] += dp[i][j-1];
            }
            dp[i][j] %= (int)1e9 + 7;
        }
    }

    cout << dp[r-1][c-1];
}
