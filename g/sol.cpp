#include<bits/stdc++.h>
#include <cstdlib>

using namespace std;

int dfs(map<int, vector<int>> &g, vector<bool> &visited, vector<int> &dp, int cur) {
    if (visited[cur]) {
        return dp[cur];
    }
    // new node
    int deepest = 0;
    for (auto i : g[cur]) {
        deepest = max(dfs(g, visited, dp, i) + 1, deepest);
    }
    visited[cur] = true;
    dp[cur] = deepest;
    return deepest;
}

int main() {
    int n, m;
    cin >> n >> m;
    map<int, vector<int>> G;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    int ans = 0;
    vector<bool> visited(n + 1, false);
    vector<int> dp(n + 1);
    for (auto i : G) {
        ans = max(dfs(G, visited, dp, i.first), ans);
    }

    cout << ans;
}
