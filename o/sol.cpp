#include<bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    vector<vector<bool>> adj(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool tmp;
            cin >> tmp;
            adj[i][j] = tmp;
        }
    }

    vector<vector<int>>dp(n, vector<int>(1 << n, 0));
    for (int i = 0; i < n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 0; i < n; i++) {
        if (adj[0][i]) {
            dp[0][1<<i] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int s = 0; s < (1 << n); s++) {
            int bit_cnt = __builtin_popcount(s);
            // skip states which we have not considered yet
            if (bit_cnt > i) {
                continue;
            }

            dp[i][s] += dp[i-1][s];
            // try adding connection from i to t
            for(int t = 0; t < n; t++) {
                if (!adj[i][t] || s & (1<<t) ) {
                    continue;
                }
                dp[i][s | (1 << t)] += dp[i-1][s];
                dp[i][s | (1 << t)] %= MOD;
            }
        }
    }

    cout << dp[n-1][(1 << n) - 1];

    // cout << endl;
    //
    // for (auto i : dp) {
    //     for (auto j : i) {
    //         cout << j << " ";
    //     }
    // }
    // cout << endl;
}
