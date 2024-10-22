#include<bits/stdc++.h>
#define ll long long 

using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<pair<ll, ll>> val(n);
    vector<vector<ll>> dp(n, vector<ll>(w + 1, 0));
    for (auto &i : val) {
        cin >> i.first >> i.second;
    }

    for (int j = 0; j <= w; j++) {
        pair<int, int> item = val[0];
        dp[0][j] = (j < item.first) ? 0 : item.second;
    }
    for (int i = 1; i < n; i++) {
        pair<int, int> item = val[i];
        for (int j = 0; j <= w; j++) {
            dp[i][j] = dp[i-1][j];
            if (j - 1 > 0) {
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
            if (j >= item.first) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - item.first] + item.second);
            }
        }
    }
    cout << dp[n-1][w];
}
