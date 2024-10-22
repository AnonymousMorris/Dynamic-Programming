#include<bits/stdc++.h>
#include <climits>
#define ll long long

using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<pair<ll, ll>> val(n);
    vector<vector<ll>> dp(n, vector<ll>(n * 1000 + 1));
    for (auto &i : val) {
        cin >> i.first >> i.second;
    }

    // first is weight, second is value
    // first iteration
    for (int j = 0; j < dp[0].size(); j++) {
        pair<int, int> item = val[0];
        dp[0][j] = (j <= item.second)? item.first : INT_MAX;
    }
    dp[0][0] = 0;

    for (int i = 1; i < n; i++) {
        pair<int, int> item = val[i];
        for (int j = dp[i].size() - 1; j >= 0; j--) {
            // previous best
            dp[i][j] = dp[i - 1][j];
            if (j < dp[i].size() - 1) {
                // best achievable for this item for value cur_val + 1
                dp[i][j] = min(dp[i][j], dp[i][j+1]);
            }
            if (j >= item.second) {
                // try using current item
                dp[i][j] = min(dp[i][j], dp[i - 1][j - item.second] + item.first);
            }
        }
    }

    // find max value achievable with weight less than W
    int ans = 0;
    for (int j = 0; j < dp[n-1].size(); j++) {
        if (dp[n-1][j] > w) {
            break;
        }
        ans = j;
    }
    cout << ans;
}
