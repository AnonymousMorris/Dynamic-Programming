#include<bits/stdc++.h>
#include <locale>
#define ll long long

using namespace std;

const ll MOD = 1000000007;

void print_arr(vector<ll> arr) {
    cout << endl;
    for (auto i : arr) {
        cout << i << " ";
    }
}

// (l, r]
ll range_sum (vector<ll> prefix, int l, int r) {
    // int l = max(l, 0);
    // cout << "debug: " << l << " " << r;
    r = min(r, (int)prefix.size() - 1);
    int size = prefix.size();

    if (l < 0) {
        return prefix[r] + prefix[size - 1] - prefix[size + l];
    }
    else {
        return prefix[r] - prefix[l] + MOD;
    }
}

ll sol(int idx, bool used_max, vector<int> &val, map<pair<int, bool>, ll> &dp, map<pair<int, bool>, bool> &visited) {
    pair<int, bool> state = {idx, used_max};
    if (visited[state]) {
        return dp[state];
    }
    ll ans = 0;
    if (used_max) {
        ans += sol(idx+1, true, val, dp, visited);
    }
}



int main() {
    string s;
    cin >> s;
    int n, d;
    cin >> d;

    n = s.length();
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        val[i] = s[i] - '0';
    }
    vector<ll>dp(d, 0), dp_last(d, 0), prefix(d, 0);

    for (int i = 1; i <= val[0]; i++) {
        dp_last[i % d] += 1;
    }
    prefix[0] = dp_last[0];
    for (int i = 1; i < d; i++) {
        prefix[i] = prefix[i-1] + dp_last[i];
    }

    print_arr(dp_last);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < d; j++) {
            dp[j] = range_sum(prefix, j - val[i] - 1, j);
            // cout << "dbg: " << val[i] << endl;
            // cout << " debug2 : " << range_sum(prefix, j - val[i], j);
            dp[j] %= MOD;
            
        }
        swap(dp, dp_last);
        print_arr(dp_last);

        prefix[0] = dp_last[0];
        for (int i = 1; i < d; i++) {
            prefix[i] = prefix[i-1] + dp_last[i];
            prefix[i] %= MOD;
        }
    }

    cout << dp_last[0];
}
