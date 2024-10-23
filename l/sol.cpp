#include<bits/stdc++.h>
#include <cstring>
#define ll long long

using namespace std;
bool visited[3001][3001];
ll dp[3001][3001];

ll solve(int i, int j, vector<ll> &a, bool first) {
    if (j < i) {
        return 0;
    }
    if (visited[i][j]) {
        return dp[i][j];
    }
    ll ans;     
    if (first) {
        ans = max(solve(i+1, j, a, !first) + a[i], solve(i, j-1, a, !first) + a[j]);
    }
    else {
        ans = min(solve(i+1, j, a, !first) - a[i], solve(i, j-1, a, !first) - a[j]);
    }
    visited[i][j] = true;
    dp[i][j] = ans;
    return ans;
}

int main() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (auto &i : a) {
        cin >> i;
    }

    memset(visited, false, sizeof(visited));

    cout << solve(0, n-1, a, true);
}
