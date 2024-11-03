#include<bits/stdc++.h>
#include <locale>
#define ll long long

using namespace std;

const int MOD = 1000000007;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    int d, n;
    cin >> s;
    cin >> d;

    // converting char to int
    n = s.length();
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        val[i] = s[i] - '0';
    }

    // // dp
    vector<vector<ll>> precompute(n, vector<ll>(d, 0));
    // first column
    for (int i = 0; i < 10; i++) {
        precompute[n-1][i % d] += 1;
    }

    for (int i = n-2; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < d; k++) {
                precompute[i][(j+k) % d] += precompute[i+1][k];
                precompute[i][(j+k) % d] %= MOD;
            }
        }
    }

    ll ans = 0;
    ll rem = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < val[i]; j++) {
            ans += precompute[i+1][(d+d-j-rem)%d];
            ans %= MOD;
        }
        rem += val[i];
        rem %= d;
    }
    // final iteration
    for (int i = 0; i <= val[n-1]; i++) {
        if ((rem + i) % d == 0) {
            ans++;
        }
    }
    ans--;
    ans += MOD;
    ans %= MOD;

    cout << ans;
}

