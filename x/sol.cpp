#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct block {
    int weight, stress, value;
};

const int MAX_TOT_WEIGHT = 20001;

int main() {
    int n;
    cin >> n;
    vector<block> val(n);
    for (auto &i : val) {
        cin >> i.weight >> i.stress >> i.value;
    }
    sort (val.begin(), val.end(), [](block a, block b) {
              return (a.stress + a.weight) < (b.stress + b.weight);
          });

    vector<vector<ll>> dp(n, vector<ll>(MAX_TOT_WEIGHT, 0));
         
    for (int j = val[0].weight; j < MAX_TOT_WEIGHT; j++) {
        int value = val[0].value;
        dp[0][j] = value;
    }

    for (int i = 1; i < n; i++) {
        block block = val[i];
        for (int j = 1; j < MAX_TOT_WEIGHT; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            
            int w_prev = j - block.weight;
            if (w_prev <= block.stress && w_prev >= 0)  {
                dp[i][j] = max(dp[i][j], block.value + dp[i-1][w_prev]);
            }
        }
    }

    cout << dp[n-1][MAX_TOT_WEIGHT - 1];
}
