#include<bits/stdc++.h>
#include <climits>
#include <cstring>
#define ll long long

using namespace std;

ll dp[400][400];
ll prefix[400];
ll a[400];
bool visited[400][400];


ll range_sum(int l, int r) {
    if (l < 0) {
        return prefix[r];
    }
    return prefix[r] - prefix[l];
}

ll solve(int i, int j){
    if (visited[i][j]) {
        return dp[i][j];
    }
    if (i == j) {
        return 0;
    }
    ll ans = LONG_LONG_MAX;
    for (int k = i; k < j; k++) {
        ll newCost = solve(i, k) + solve(k+1, j) + range_sum(i-1, j);
        ans = min(ans, newCost);
    }
    visited[i][j] = true;
    dp[i][j] = ans;
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    prefix[0] = a[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + a[i];
    }
    memset(visited, false, sizeof(visited));

    cout << solve(0, n-1);
}
