#include<bits/stdc++.h>
#include <cstring>

using namespace std;

double dp[301][301][301];
bool visited[301][301][301];

double dfs(int i, int j, int k, int n) {
    if (i < 0 || j < 0 || k < 0) {
        return 0;
    }
    if (visited[i][j][k]) {
        return dp[i][j][k];
    }
    double ans = 0;
    int cnt = i + j + k;

    ans += dfs(i-1, j, k, n) * (double) i;
    ans += dfs(i+1, j-1, k, n) * (double) j;
    ans += dfs(i, j+1, k-1, n) * (double) k;
    ans /= (double) cnt;
    ans += n / (double) cnt;
    visited[i][j][k] = true;
    dp[i][j][k] = ans;
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); 
    std::cout << std::fixed << std::setprecision(10);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }

    dp[0][0][0] = 0;
    memset(visited, false, sizeof(visited));
    visited[0][0][0] = true;

    vector<int> freq(4, 0);
    for (auto i : a) {
        freq[i]++;
    }

    cout << dfs(freq[1], freq[2], freq[3], n) << endl;
}
