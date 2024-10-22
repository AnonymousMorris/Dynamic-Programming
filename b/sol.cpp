#include<bits/stdc++.h>
#include <climits>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), dp(n, INT_MAX);
    for(auto &i : a) {
        cin >> i;
    }

    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k && i - j >= 0; j ++) {
            dp[i] = min(dp[i - j] + abs(a[i] - a[i - j]), dp[i]);
        }
    }
    cout << dp[n - 1];
}
