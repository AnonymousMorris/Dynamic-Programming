
#include<bits/stdc++.h>
#define ll long long

using namespace std;
map<pair<int, int>, ll> dp, prefix;
map<pair<int, int>, bool> visited, prefix_visited;

ll sol(int node, int from, vector<vector<int>> &tree, int m) {
    pair<int, int> state = {node, from};
    if (visited[state]) {
        return dp[state];
    }
    if (tree[node].size() == 1 && tree[node][0] == from) {
        return 2;
    }

    ll ans = 1;
    ll child_ans = 1;
    for (auto i : tree[node]) {
        if (i == from) {
            continue;
        }
        else {
            child_ans *= sol(i, node, tree, m);
            child_ans %= m;
        }
    }
    ans += child_ans;
    ans %= m;
    visited[state] = true;
    dp[state] = ans;
    return ans;
}

ll calculate_prefix(int node, int from, vector<vector<int>> &tree, int m) {
    pair<int, int> state = {node, from};
    if (prefix_visited[state]) {
        return prefix[state];
    }

    ll ans = sol(node, from, tree, m);
    for (auto i : tree[node]) {
        if (i == from) {
            continue;
        }
        else {
            ans += calculate_prefix(i, node, tree, m);
            ans %= m;
        }
    }
    prefix_visited[state] = true;
    prefix[state] = ans;
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> tree(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }


    for (int i = 0; i < n; i++) {
        ll ans = 1;
        ans = sol(i, -1, tree, m) - 1;
        if (ans < 0) {
            ans += m;
        }
        // for (auto j : tree[i]) {
        //     // ans *= calculate_prefix(j, i, tree, m);
        //     ans %= m;
        // }
        cout << ans << "\n";
    }

    // cout << endl;
    //
    // for (auto i : tree) {
    //     for (auto j : i) {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
    //
    // cout << endl;
    // for (auto i : dp) {
    //     cout << i.first.first << " " << i.first.second << ": " << i.second << endl;
    // }


    // cout << sol(0, -1, tree, m);
}

