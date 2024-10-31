#include<bits/stdc++.h>
#define ll long long

using namespace std;
const ll MOD = 1000000007;

void merge(vector<vector<ll>> &a, vector<vector<ll>> &b, vector<vector<ll>> &ans, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans [i][j] = 0;
            for (int l = 0; l < n; l++) {
                ans[i][j] += a[i][l] * b[l][j];
                ans[i][j] %= MOD;
            }
        }
    }
}


int main() {
    int n;
    ll k;
    cin >> n >> k;
    vector<vector<bool>> adj(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool tmp;
            cin >> tmp;
            adj[i][j] = tmp;
        }
    }

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<ll>> dp_last(n, vector<ll>(n, 0));
    vector<vector<ll>> ans(n, vector<ll>(n, 0));
    vector<vector<ll>> ans_last(n, vector<ll>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp_last[i][j] = adj[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        ans_last[i][i] = 1;
    }
    if (k & 1) {
        merge(ans_last, dp_last, ans, n);
        swap(ans, ans_last);
    }

    for(ll l = 2; l <= k; l<<=1) {
        merge(dp_last, dp_last, dp, n);
        if (l & k) {
            merge(dp, ans_last, ans, n);
            swap(ans, ans_last);
        }
        swap(dp, dp_last);
    }

    int ll ans_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans_sum += ans_last[i][j];
            ans_sum %= MOD;
        }
    }
    cout << ans_sum;

    cout << endl;
}
