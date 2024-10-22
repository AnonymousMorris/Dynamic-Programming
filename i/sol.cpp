#include<bits/stdc++.h>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); 
    std::cout << std::fixed << std::setprecision(10);

    int n;
    cin >> n;
    vector<double> p(n);
    for (auto &i : p) {
        cin >> i;
    }
    
    vector<vector<double>> dp(n, vector<double>(n+1, 0));
    dp[0][1] = p[0];
    dp[0][0] = 1 - p[0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j == 0) {
                dp[i][0] = dp[i-1][0] * (1 - p[i]);
                continue;
            }
            dp[i][j] = dp[i-1][j] * (1 - p[i]) + dp[i-1][j-1] * p[i];
        }
    }

    double ans = 0;
    for (int i = (n + 1) / 2; i < n+1; i++) {
        ans += dp[n-1][i];
    }
    cout << ans;
}
