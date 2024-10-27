#include <bits/stdc++.h>

using namespace std;

const int maxK = 5001;
int main() {
    int n, k;
    cin >> n >> k;
    int h = maxK*2+10;
    double p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    sort(p, p + n);
    reverse(p, p+n);


    double dp[n][maxK*2+10];
    double prefix[h];
    memset(dp, 0, sizeof(dp));
    memset(prefix, 0, sizeof(prefix));

    // let m represent 0
    int m = maxK / 2;
    dp[0][m+1] = p[0];
    dp[0][m-1] = 1 - p[0];

    
    for (int i = 1; i < h; i++) {
        prefix[i] = prefix[i-1] + dp[0][i];
    }

    double ans = 0;
    double tmp = 0;
    for (int l = m + k; l < h; l++) {
        tmp += dp[0][l];
    }
    ans = max(tmp, ans);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < h; j++) {
            dp[i][j] = 0;
            if (j != 0) {
                dp[i][j] += p[i] * dp[i-1][j-1];
            }
            if (j != h - 1) {
                dp[i][j] += (1 - p[i]) * dp[i-1][j+1];
            }
            if (j != 0)
            prefix[j] = prefix[j-1] + dp[i][j];
        }
        double tmp = 0;
        for (int l = m + k; l < h; l++) {
            tmp += dp[i][l];
        }
        ans = max(tmp, ans);
        // ans = max(prefix[h-1] - prefix[m + k - 1], ans);
    }

    cout << ans;

    // cout << endl;
    // for (int i = 0 ; i < n; i++) {
    //     for (int j = m - 5; j < m + 5; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}#include <bits/stdc++.h>

using namespace std;

const int maxK = 5001;
int main() {
    int n, k;
    cin >> n >> k;
    int h = maxK*2+10;
    double p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    sort(p, p + n);
    reverse(p, p+n);


    double dp[n][maxK*2+10];
    double prefix[h];
    memset(dp, 0, sizeof(dp));
    memset(prefix, 0, sizeof(prefix));

    // let m represent 0
    int m = maxK / 2;
    dp[0][m+1] = p[0];
    dp[0][m-1] = 1 - p[0];

    
    for (int i = 1; i < h; i++) {
        prefix[i] = prefix[i-1] + dp[0][i];
    }

    double ans = 0;
    double tmp = 0;
    for (int l = m + k; l < h; l++) {
        tmp += dp[0][l];
    }
    ans = max(tmp, ans);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < h; j++) {
            dp[i][j] = 0;
            if (j != 0) {
                dp[i][j] += p[i] * dp[i-1][j-1];
            }
            if (j != h - 1) {
                dp[i][j] += (1 - p[i]) * dp[i-1][j+1];
            }
            if (j != 0)
            prefix[j] = prefix[j-1] + dp[i][j];
        }
        double tmp = 0;
        for (int l = m + k; l < h; l++) {
            tmp += dp[i][l];
        }
        ans = max(tmp, ans);
        // ans = max(prefix[h-1] - prefix[m + k - 1], ans);
    }

    cout << ans;

    // cout << endl;
    // for (int i = 0 ; i < n; i++) {
    //     for (int j = m - 5; j < m + 5; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}
