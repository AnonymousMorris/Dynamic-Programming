#include<bits/stdc++.h>
#define ll long long

using namespace std;

static const ll MOD = 1000000007;

int main() {
    int n;
    string s;
    cin >> n >> s;

    vector<vector<ll>> dp(n, vector<ll>(n + 1, 0));
    vector<ll> prefix(n + 1, 0);

    // first iteration of dp
    prefix[1] = 1;
    dp[0][1] = 1;

    // rest of dp
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i + 1; j++) {
            if (s[i-1] == '<') {
                dp[i][j] = prefix[j-1] % MOD;
            }
            else {
                dp[i][j] = (prefix[i] - prefix[j - 1] + MOD) % MOD;
            }
        }
        prefix[1] = dp[i][1];
        for (int j = 2; j <= n; j++) {
            prefix[j] = prefix[j - 1] + dp[i][j];
            prefix[j] %= MOD;
        }
    }

    ll ans = 0;
    for (auto i : dp[n-1]) {
        ans += i;
        ans %= MOD;
    }
    cout << ans;
}

