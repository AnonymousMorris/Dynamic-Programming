#include<bits/stdc++.h>

using namespace std;


bool solve(int state, vector<int> &a, vector<bool> &dp, vector<bool> &visited) {
    // base case
    if (state <= 0) {
        return false;
    }
    if (visited[state]) {
        return dp[state];
    }

    // recursive case
    // a state is winning if there is a state transition where the other player is losing
    // a state is losing if all reachable state is winning
    for (auto i : a) {
        if ( state - i < 0) {
            continue;
        }
        if ( !solve(state - i, a, dp, visited)) {
            visited[state] = true;
            dp[state] = true;
            return true;
        }
    }
    visited[state] = true;
    dp[state] = false;
    return false;
}


int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }

    vector<bool> visited(k+1, false);
    vector<bool> dp(k+1);

    if (solve(k, a, dp, visited)) {
        cout << "First";
    }
    else {
        cout << "Second";
    }

    // cout << endl;
    // for (auto i : dp) {
    //     cout << i << " ";
    // }
}
