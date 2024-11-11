#include<bits/stdc++.h>
#include <cstring>
#define ll long long

using namespace std;

const int N = 100000 + 5;
ll prefix_dp[N], suffix_dp[N];
ll prod1[N], prod2[N];
vector<ll> tree[N];
int m;

void dp_init(int node, int from) {
    suffix_dp[node] = 1;
    for (auto child : tree[node]) {
        if (child == from) continue;
        dp_init(child, node);
        suffix_dp[node] = suffix_dp[node] * (suffix_dp[child] + 1) % m;
    }

    ll pre = 1, suf = 1;
    for (int v = 0; v < tree[node].size(); v++) {
        int left = tree[node][v];
        int right = tree[node][tree[node].size() - v - 1];

        if (left != from) {
            prod1[left] = pre;
            pre = pre * (suffix_dp[left] + 1) % m;
        }
        if (right != from) {
            prod2[right] = suf;
            suf = suf * (suffix_dp[right] + 1) % m;
        }
    }
}

void dfs_dp (int node, int from) {
    if (from == -1) prefix_dp[node] = 1;
    else prefix_dp[node] = (prefix_dp[from] * prod1[node] % m * prod2[node] + 1) % m;
    for (auto child : tree[node]) {
        if (child == from) continue;
        dfs_dp(child, node);
    }
}

int main() {
    int n;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }


    dp_init(0, -1);
    dfs_dp(0, -1);

    for (int i = 0; i < n; i++) {
        ll ans = prefix_dp[i] * suffix_dp[i] % m;
        cout << ans << "\n";
    }
}
