#include<bits/stdc++.h>

using namespace std;


int main() {
    string s, t;
    cin >> s >> t;

    int n, m;
    m = s.size();
    n = t.size();

    int dp[m][n];

    dp[0][0] = (s[0] == t[0]) ? 1 : 0;
    // first column of dp
    for (int i = 1; i < n; i++) {
        dp[0][i] = (s[0] == t[i]) ? 1 : 0;
        dp[0][i] = max(dp[0][i-1], dp[0][i]);
    }
    // first row of dp
    for (int i = 1; i < m; i++) {
        dp[i][0] = (s[i] == t[0]) ? 1 : 0;
        dp[i][0] = max(dp[i][0], dp[i-1][0]);
    }
    // rest of dp
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            bool match = s[i] == t[j];
            dp[i][j] = max({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]+match});
        }
    }

    // back tracking
    string ans = "";
    int i, j;
    i = m - 1;
    j = n - 1;
    while (i >=0 && j >= 0) {
        if (dp[i][j] == 0) {
            break;
        }
        if (j > 0 && dp[i][j-1] == dp[i][j]) {
            j--;
            continue;
        }
        if (i > 0 && dp[i-1][j] == dp[i][j]) {
            i--;
            continue;
        }

        ans += t[j];
        j--;
        i--;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
}
