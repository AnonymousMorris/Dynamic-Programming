#include<bits/stdc++.h>
#define ll long long

using namespace std;
const ll MOD = 1000000007;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }

    vector<vector<ll>> dp(n, vector<ll>(k + 1, 0));
    vector<ll> prefix(k + 1);
    vector<ll> newPrefix(k + 1);
    prefix[0] = 1;
    dp[0][0] = 1;
    for (int i = 1; i <= k; i++) {
        if (i <= a[0]) {
            dp[0][i] = 1;
        }

        prefix[i] = prefix[i-1] + dp[0][i];
        prefix[i] %= MOD;
    }

    for (int i = 1; i < n; i++) {
        dp[i][0] = 1;
        newPrefix[0] = 1;
        for (int j = 1; j <= k; j++) {
            int range_min = j - a[i] - 1;
            int range_max = j;

            if (range_min < 0) {
                dp[i][j] = prefix[range_max];
            }
            else {
                dp[i][j] = prefix[range_max] - prefix[range_min] + MOD;
            }
            newPrefix[j] = (newPrefix[j-1] + dp[i][j]);

            dp[i][j] %= MOD;
            newPrefix[j] %= MOD;
        }
        swap(prefix, newPrefix);
    }

    cout << dp[n-1][k] << endl;

    // cout << endl;
    // for (auto i : dp) {
    //     for (auto j : i) {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }

}
