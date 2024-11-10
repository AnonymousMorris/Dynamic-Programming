#include <bits/stdc++.h>

using namespace std;


int main() {
    int c, n;
    cin >> c >> n;
    vector<int> val(n);
    for (auto &i : val) {
        cin >> i;
    }

    c++;
    vector<vector<bool>> visited(c, vector<bool>(c, false));
    vector<pair<int, int>> dp;
    visited[0][0] = true;
    dp.push_back({0, 0});
    for (int i = 0; i < n; i++) {
        int song = val[i];
        int maxsize = dp.size();
        for (int x = 0; x < maxsize; x++) {
            auto j = dp[x];
            int a = j.first + song;
            int b = j.second;
             //cout << a << ' ' << b << endl;
            if (a < c && b < c) {
                    //assert(a >= 0 && b >= 0);
                if (!visited[a][b]) {
                    visited[a][b] = true;
                    dp.push_back({a, b});
                }
            }
             a = j.first;
             b = j.second + song;
             //cout << a << ' ' << b << endl;
            if (a < c && b < c) {
                if (!visited[a][b]) {
                    //assert(a >= 0 && b >= 0);
                    visited[a][b] = true;
                    dp.push_back({a, b});
                }
            }
        }
    }

    pair<int, int> ans = {0, 0};
    for (auto i : dp) {
        int tot = i.first + i.second;
        int ansTot = ans.first + ans.second;
        if (tot > ansTot) {
            ans = i;
        }
        else if (tot == ansTot) {
            if (abs(i.first - i.second) < abs(ans.first - ans.second)) {
                ans = i;
            }
        }
    }
    cout << max(ans.first, ans.second) << " " << min(ans.first, ans.second);
}
