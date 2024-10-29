#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n), b(n);
    for (auto &i : h) {
        cin >> i;
    }
    for (auto &i : b) {
        cin >> i;
    }

    map<ll, ll> dp;
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        // consider using flower i
        map<ll, ll>::iterator it = dp.lower_bound(h[i]);
        ll tmp;
        if (it == dp.begin()) {
            // there is no other dp with height less than height_i
            dp[h[i]] = b[i];
        }
        else {
            // precondition: dp is not empty
            it--;
            dp[h[i]] = it->second + b[i];
        }
        tmp = dp[h[i]];
        // get iterator to after the node we just inserted
        it = dp.upper_bound(h[i]);
        // erase all dp with height greater than h[i] and value less than dp[i]
        while(it != dp.end()) {
            if (it-> second > tmp) {
                break;
            }
            it = dp.erase(it);
        }
    }

    cout << (dp.rbegin()) ->second;
}
