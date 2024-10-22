#include<bits/stdc++.h>

using namespace std;


int main() {
    string s, t;
    cin >> s >> t;

    int n, m;
    m = s.size();
    n = t.size();

    int dp[m][n];

    for (int i = 0; i < n; i++) {
        dp[0][i] = (s[0] == t[i]) ? 1 : 0;
        if (i != 0) {
            dp[0][i] = max(dp[0][i-1], dp[0][i]);
        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            bool match = s[i] == t[j];
            dp[i][j] = dp[i-1][j];
            if (j != 0) {
                dp[i][j] = max(dp[i-1][j-1] + match, dp[i][j]);
                dp[i][j] = max(dp[i][j-1], dp[i][j]);
            }
        }
    }

    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    string ans = "";
    int i, j, tmp;
    i = m - 1;
    j = n - 1;
    tmp = dp[m-1][n-1];
    while (i >=0 && j >= 0) {
        if (j > 0 && dp[i][j-1] == dp[i][j]) {
            j--;
            continue;
        }
        if (i > 0 && dp[i-1][j] == dp[i][j]) {
            i--;
            continue;
        }


        if (j > 0) {
            if (dp[i][j-1] == dp[i][j]) {
                j--;
            }
            else {
                if (i > 0) {
                    if (dp[i-1][j] == dp[i][j]) {
                        i--;
                        continue;
                    }
                }
                ans += t[j];
                i--;
                j--;
            }
        }
        else {
            if (dp[i][j] == 1) {
                ans += t[j];
            }
            j--;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    // cout << dp[m-1][n-1];
}
