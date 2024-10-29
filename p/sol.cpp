#include<bits/stdc++.h>
#define ll long long

using namespace std;
const ll MOD = 1000000007;

// first is the number of ways where the node is white
// second is the number of ways where the node is black
pair<ll, ll> dfs(vector<vector<int>> &tree, vector<pair<ll, ll>> &dp, vector<bool> &visited, int node, int from) {
    if (visited[node]) {
        return dp[node];
    }

    pair<ll, ll> ans = {1, 1};
    for (auto i : tree[node]) {
        if (i == from) {
            continue;
        }

        pair<ll, ll> tmp = dfs(tree, dp, visited, i, node);
        ans.second *= tmp.first;
        ans.first *= (tmp.first + tmp.second) % MOD;
        ans.first %= MOD;
        ans.second %= MOD;
    }
    visited[node] = true;
    dp[node] = ans;
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> tree(n, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u-1].push_back(v-1);
        tree[v-1].push_back(u-1);
    }

    vector<pair<ll, ll>>dp(n);
    vector<bool>visited(n, false);

    ll ans = 0;
    pair<ll, ll> tmp = dfs(tree, dp, visited, n-1, -1);
    ans = tmp.first + tmp.second;
    ans %= MOD;
    cout << ans;
}
