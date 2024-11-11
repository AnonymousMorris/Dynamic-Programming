#include<bits/stdc++.h>
#include <climits>
#include <variant>
#define ll long long

using namespace std;

int n;
ll score(int state, vector<vector<ll>> &val) {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if ((1 << i) & state) {
            for (int j = i + 1; j < n; j++) {
                if ((1 << j) & state) {
                    ans += val[i][j];
                }
            }
        }
    }
    return ans;
}

ll sol(int state, vector<bool>&visited, vector<ll> &dp, vector<ll> &cost) {
    if (visited[state]) {
        return dp[state];
    }

    dp[state] = cost[state];
    for (int m = state; m != 0; m = (m-1)&state) {
        // int allBits = (1 << n) - 1;
        int other = state ^ m;
        dp[state] = max(dp[state], cost[m] + sol(other, visited, dp, cost));
    }

    visited[state] = true;
    return dp[state];

}

void print_bit (int state) {
    for (int i = 0; i < n; i++) {
        cout << ((state >> (n-i-1)) & 1);
    }
}

int main() {
    cin >> n;
    vector<vector<ll>> val(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> val[i][j];
        }
    }

    vector<ll> cost(1 << n);
    vector<ll> dp(1 << n, LONG_LONG_MIN);
    vector<bool> visited(1 << n, false);
    for (int i = 0; i < 1 << n; i++) {
        cost[i] = score(i, val);
    }

    // ll ans = LONG_LONG_MIN;
    for (int s = 0; s < (1 << n); s++) {
        dp[s] = cost[s];
        for (int m = s; m != 0; m = (m-1)&s) {
            int allBits = (1 << n) - 1;
            int other = allBits ^ m;
            dp[s] = max(dp[s], cost[m] + dp[other]);
        }
    }

    ll ans = sol((1 << n) - 1, visited, dp, cost);

    cout << ans;
}
