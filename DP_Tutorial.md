# Dynamic Programming

[toc]

## Introduction

Dynamic programming (DP) is my favorite topic and it's one of the most powerful topics in competitive programming with connections to a variety of other topics. Dynamic Programming is my specialty and I believe that I have an approach to Dynamic Programming that does not yet commonly exist on paper. In this blog post, I will walk through the core principles behind dynamic programming starting basic enough but each new chapter building on the ideas of the last. 

This is a condensation of the insights I gained on DP. I have a unabridged blog which contains my eureka moment for all 26 problems from the Atcoder DP contest. The Atcoder DP contest is a collection of the most classic DP problems and essential if you want to get good at DP. Almost every ICPC DP problem I have seen so far can be mapped to similar Atcoder DP problem.  

## Thinking Backwards

Change your perspective from "Now that I am at x, where should I go to next?" into "In order to get to X, where could I have came from?"

### Problem [Frog]{https://atcoder.jp/contests/dp/tasks/dp_a}

There are **n** pillars with the height of the *ith* pillar being **a<sub>i</sub>**. A frog is able to jump from position **i** to position **i+1** or **i+2**. A cost is incurred when the frog jump from one pillar to another with the cost being the difference in height of the two pillar. 

What is the minimum cost to start from pillar **1** and arrive at pillar **n**?

### Wrong Approach

Traditional thinking might have us start thinking from the perspective of the frog. We are trying to get the frog to the end after all so naturally one might start thinking "where can the frog jump to from here?". 

There would be two spots the frog can jump to and the reader might start thinking about maybe I can take the cheapest step first

![From the perspective of the frog](/home/ghost/notes/blogs/Frog_perspective.png)

Relatively easily, one might realize the the two squares it can jump to can also jump to different squares so it seems like we might have to take all those into account.

![Frog propagated to the end](/home/ghost/notes/blogs/frog_propagate.png)

### Recursive Approach

Instead of asking where the frog can go, let's ask where could the frog have came from? 

To arrive at index 3, it must come from either index 1 or index 2. 

To arrive at index k, it must come from either index k-1 or k-2. 

Imagine that we are at index n (the last index). Assume that we know the minimum cost to get to n-1, and n-2. Can we figure out the minimum cost to get to n?

Mathematically, what I describe in words can be written succinctly as the equation below.  

```c++
dp[i] = min(dp[i-1] + cost(i-1, i), dp[i-2]+ cost(i-2, i))
```

dp[i] is minimum cost to get to i

cost(i, j) is cost to jump from i to j

### Code

```c++
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), dp(n);
    for (auto &i: a) {
        cin >> i;
    }

    dp[0] = 0;
    dp[1] = abs(a[1] - a[0]);
    for (int i = 2; i < n; i++) {
        dp[i] = min(dp[i-1] + abs(a[i] - a[i - 1]) ,dp[i - 2] + abs(a[i] - a[i-2]));
    }
    cout << dp[n-1];
}
```

### Conclusion

Shift your perspective, think recursively. Sometimes, computing future is hard but computing the past is easy. Some very hard problems become very easy when you look at a problem in terms of "what do information do I need to solve up to index i?"



## Area of Influence

When we make a decision, how long will the decision still have an effect? In the frog problem, the decision to jump 1 square or jump 2 squares have a effect up to position X + 2. After X + 2, it really doesn't matter how you got to X + 2. 

The idea of this chapter is to look closely at the area of influence for every decision. This idea is powerful because after a decision no longer have any influence, then it doesn't matter how you got the answer to the subproblem because how you got the answer doesn't affect anything after you passed the area of influence.

### Problem: [Vocation]{https://atcoder.jp/contests/dp/tasks/dp_c}


Taro is on vocation for **N** days. Each day, Taro can choose what activity he wants to do. Activity **A**, **B**, or **C**. Each activity will give some amount of happiness 

(**a<sub>i</sub>** points of happiness for activity **A** on day **i**, **b<sub>i</sub>** points of happiness for activity **B** on day **i**, **c<sub>i</sub>** points of happiness for activity **C** on day **i**.

An additional constraint is that Taro *cannot* do the same activity for 2 days in a row. 

What is the maximum amount of happiness Taro can gain from this vocation?

### Idea

What is the area of influence of picking activity a, b, or c?

The decisions affected is only the next decision. 

![](/home/ghost/notes/blogs/vocation_dp.png)

Green is the decision

Red is the affected area of decision

Mathematically and recursively, the DP would be DP<sub>i</sub> is only affected by DP<sub>i-1</sub> with the special restriction of not picking the same activity twice in a row.

```c++
dp[i][0] = max(dp[i-1][1], dp[i-1][2]) + val[i][0]; // max happiness up to day i where activity a is chosen for day i
dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + val[i][1]; // max happiness up to day i where activity b is chosen for day i
dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + val[i][2]; // max happiness up to day i where activity c is chosen for day i
```

### Code

```c++
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> val(n, vector<int>(3));
    vector<vector<int>> dp(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> val[i][0] >> val[i][1] >> val[i][2];
    }

    dp[0][0] = val[0][0];
    dp[0][1] = val[0][1];
    dp[0][2] = val[0][2];
    for (int i = 1; i < n; i++) {
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + val[i][0];
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + val[i][1];
        dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + val[i][2];
    }

    cout << max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
}
```

### Conclusion

Look at the area of effect of a decision. Store everything within the area of effect.



## Dense Array

Sometimes, the value you are optimizing for isn't explicitly given to you. However, if the max value is small enough, we can ask the question of "can you have value 1, value 2, value 3, ... up to value V". 

### Problem: [Knapsack]{https://atcoder.jp/contests/dp/tasks/dp_d}

There are **N** items with the **i<sup>th</sup>** item having weight **w<sub>i</sub>** and value **v<sub>i</sub>**. 

What is the maximum value possible if the total capacity of the knapsack is weight **W**? 

### Input

1 &le; N &le; 100

1 &le; W &le; 10<sup>5</sup>

1 &le; w<sub>i</sub> &le; W

1 &le; v<sub>i</sub> &le; 10<sup>9</sup>

### Idea

When having to select the optimal combinations of items, we can consider one item at a time. Then it becomes a binary choice of to include or not to include the item. (This also requires that **N** is small)

Another insight is that when the maximum **W** is small enough, you can turn the DP into one on the dense representation of W (1, 2, ... W) instead only w<sub>i</sub> or some other categorical values (if you excuse the abuse of vocabulary). 

Construct a 2D DP where the x-axis is item 1, item 2, ... item **N** and y-axis is weight 1, weight 2, ... weight W (Dense y-axis)

![Knapsack DP Array Illustration](/home/ghost/notes/blogs/knapsack_dp.png)

Mathematically, the DP array can be written as

```c++
// dp[i][j] is maximum value possible using items 1 up to i with a total weight of j or less
dp[i][j] = max({dp[i-1][j-w[i]], dp[i][j-1], dp[i-1][w]});
```

### Code

``` c++
#include<bits/stdc++.h>
#define ll long long 

using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<pair<ll, ll>> val(n);
    vector<vector<ll>> dp(n, vector<ll>(w + 1, 0));
    for (auto &i : val) {
        cin >> i.first >> i.second;
    }

    for (int j = 0; j <= w; j++) {
        pair<int, int> item = val[0];
        dp[0][j] = (j < item.first) ? 0 : item.second;
    }
    for (int i = 1; i < n; i++) {
        pair<int, int> item = val[i];
        for (int j = 0; j <= w; j++) {
            dp[i][j] = dp[i-1][j];
            if (j - 1 > 0) 
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            if (j >= item.first) 
                dp[i][j] = max(dp[i][j], dp[i - 1][j - item.first] + item.second);
        }
    }
    cout << dp[n-1][w];
}
```



## Everything is State

Index i, index j, index blah blah blah. 

All that those numbers are doing is representing **STATE**. The is no reason that state has to conform to the limitation of being represented by a few numbers. 

When we do DP, we are doing dp on some indexes, we are doing dp on **STATE**. 

Index i and index j was just good ways to represent state for those earlier problems but that way of thinking is quite limiting.

### Problem: [Sushi]{https://atcoder.jp/contests/dp/tasks/dp_j}

Throw **N** coins each with probability **p<sub>i</sub>** of being heads, what is the probability of having more heads than tails?

### Input 

**N** is an odd number

1 &le; **N** &le; 2999

**p<sub>i</sub>** is a real number with 2 decimal places

0 &le; **p<sub>i</sub>** &le; 1

### Idea

This problems boils down to how to encode the state efficiently. We could have **N** numbers with each number representing the number of sushi left on that particular plate. However, that would be an encoding with **N** dimensions, 300 dimension in this case, which is infeasible. 

The insight then comes from finding the symmetry in the problem. In this case, the symmetry comes from the fact that every plate has equal probability of being chosen. So every plate with 3 sushi can be treated identically. 

Mathematically, the picking a plate with x sushi transitions the state to 1 more plate of x-1 sushi, and 1 less plate of x sushi

```c++
// Let P(1 | state) be the probability of picking a plate with 1 sushi, P(2 | state) be plate with 2 sushi and so on.
dp[i][j][k] = P(1 | state) * dp[i-1][j][k] + P(2 | state) * dp[i+1][j-1][k] + P(3 | state) * dp[i][j+1][k-1] + P(0 | state)
```

### Code

```c++
#include<bits/stdc++.h>
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
```



## Even More Backwards

There are two things in a graph, vertices (state) and edges (transition / action). 

Internalize the idea of working backwards from the result. Ask yourself, "What is the last **action** you take?"

### Problem: [Slimes]{https://atcoder.jp/contests/dp/tasks/dp_n}

There are **N** slimes which can be merged with adjacent slimes. Each slime has a size of **a<sub>i</sub>** and the cost of merging two slimes is **x + y** where **x** is the cost of the left slime and **y** is the cost of the right slime.

What is the minimum cost to merge all **N** slime?

### Input

2 &le; **N** &le; 400

1 &le; **a<sub>i</sub>** &le; 10<sup>9</sup>

### Idea

The "action" we do in this problem is merging. From that, we can see that we can use dp to solve the sub problem of optimal left and optimal right slime.

What are the possible states? 

Ans: All possible ranges between 1 and 400, (ie, **n<sup>2</sup>**)

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll dp[400][400];
ll prefix[400];
ll a[400];
bool visited[400][400];

ll range_sum(int l, int r) {
    if (l < 0) 
        return prefix[r];
    return prefix[r] - prefix[l];
}

ll solve(int i, int j){
    if (visited[i][j]) 
        return dp[i][j];
    if (i == j) 
        return 0;
    ll ans = LONG_LONG_MAX;
    for (int k = i; k < j; k++) {
        ll newCost = solve(i, k) + solve(k+1, j) + range_sum(i-1, j);
        ans = min(ans, newCost);
    }
    visited[i][j] = true;
    dp[i][j] = ans;
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    prefix[0] = a[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + a[i];
    }
    memset(visited, false, sizeof(visited));

    cout << solve(0, n-1);
}
```

