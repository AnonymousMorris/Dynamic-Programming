# Every DP trick

This blog post is a compiled list of insights I gained on Dynamic Programming from the [Atcoder DP Contest][https://atcoder.jp/contests/dp]. I will summarize the problem statement for each problem but if there is any confusion due to the brevity, feel free to check out the official problem on Atcoder. The problem statements on Atcoder are all quite well written. 

## What is Dynamic Programming

Dynamic Programming (DP) is my favorite area in competitive programming. At its core, DP is about breaking a problem down into subproblems where the subproblems are easier to solve and can be easily combined to form the solution to the whole problem once it is solved. The key to being good at DP is being able to recognize how you can reorganize the problem and the dependence relation of each subproblem which gives hints to how you can structure your DP. 

One excellent resource for learning DP is the [atcoder dp contest][https://atcoder.jp/contests/dp]. The contest consist of 26 classic dynamic problems arranged in increasing levels of difficulty with each problem displaying a unique new trick to DP. In this blog, I try to generalize the lesson of each problem so that they might be applied to all dynamic programming problem. The main focus is on the insight I learned rather than the solution itself because there is already an excellent [editorial][https://nwatx.me/post/atcoderdp] by Neo Wang.

## List of insights

### [A: Frog 1][https://atcoder.jp/contests/dp/tasks/dp_a] 

#### Problem Statement: 

There are **n** pillars with the height of the *ith* pillar being **a<sub>i</sub>**. A frog is able to jump from position **i** to position **i+1** or **i+2**. A cost is incurred when the frog jump from one pillar to another with the cost being the difference in height of the two pillar. 

What is the minimum cost to start from pillar **1** and arrive at pillar **n**?

#### Insight: 

Oftentimes, rather than thinking of what destination the frog can jump to, we can think of the problem in terms of where the frog can come from. 

More generally, we realize that when solving DP problems, we do not need to follow chronological order. Instead, it is often helpful to think in reverse order as that makes it easier to find the recurrence relation.

### [B: Frog 2][https://atcoder.jp/contests/dp/tasks/dp_b]

#### Problem Statement:

There are **n** pillars with the height of the *i<sup>th</sup>* pillar being **a<sub>i</sub>**. A frog is able to jump from position **i** to position **i+1**, **i+2**, ..., **i+k**. A cost is incurred when the frog jump from one pillar to another with the cost being the difference in height of the two pillar. 

What is the minimum cost to start from pillar **1** and arrive at pillar **n**?

(Same problem as A except the frog can jump up to K steps forward.)

#### Insight: 

The key lesson this problem teaches is that you can generalize a result to any number once you understood the power of thinking abstractly in terms of where a frog can jump from.

### [C: Vocation][https://atcoder.jp/contests/dp/tasks/dp_c]

#### Problem Statement: 

Taro is on vocation for **N** days. Each day, Taro can choose what activity he wants to do. Activity **A**, **B**, or **C**. Each activity will give some amount of happiness 

(**a<sub>i</sub>** points of happiness for activity **A** on day **i**, **b<sub>i</sub>** points of happiness for activity **B** on day **i**, **c<sub>i</sub>** points of happiness for activity **C** on day **i**.

An additional constraint is that Taro *cannot* do the same activity for 2 days in a row. 

What is the maximum amount of happiness Taro can gain from this vocation?

#### Insight

When a choice affects the next choice, we can keep track of optimal score for all choices. 

More generally, if the last state after taking some action affects the next actions, we can keep track of the optimal solution for all possible ending state. This allows us to construct the optimal solution for each successive step.

### [D: Knapsack 1][https://atcoder.jp/contests/dp/tasks/dp_d]

#### Problem Statement:

There are **N** items with the **i<sup>th</sup>** item having weight **w<sub>i</sub>** and value **v<sub>i</sub>**. What is the maximum value possible if the total capacity of the knapsack is weight **W**? 

#### Input

1 &le; N &le; 100

1 &le; W &le; 10<sup>5</sup>

1 &le; w<sub>i</sub> &le; W

1 &le; v<sub>i</sub> &le; 10<sup>9</sup>

#### Insight

When having to select the optimal combinations of items, we can consider one item at a time. Then it becomes a binary choice of to include or not to include the item. (This also requires that **N** is small)

Another insight is that when the maximum **W** is small enough, you can turn the DP into one on the dense representation of W (1, 2, ... W) instead only w<sub>i</sub> or some other categorical values (if you excuse the abuse of vocabulary). 

### [E: Knapsack 2][https://atcoder.jp/contests/dp/tasks/dp_e]

#### Problem Statement:

There are **N** items with the **i<sup>th</sup>** item having weight **w<sub>i</sub>** and value **v<sub>i</sub>**. What is the maximum value possible if the total capacity of the knapsack is weight **W**? 

(Exact same as Knapsack 1, difference is in size of inputs)

#### Input

1 &le; N &le; 100

1 &le; W &le; 10<sup>9</sup>

1 &le; w<sub>i</sub> &le; W

1 &le; v<sub>i</sub> &le; 10<sup>3</sup>

#### Insight

This problem is the same as Knapsack 1 but what it is trying to teach us is that sometimes there are symmetries on the different values in a DP. In this case, we see that rather than *maximizing* the value to achieve some weight [1, W], we can also maximize the weight for all values [1, V]

In Knapsack 1, we chose weights [1, W] on the y axis because W is smaller (10<sup>5</sup> compared to 10<sup>9</sup>).

In Knapsack 2, we chose values [1, V] on the y axis because V is smaller (10<sup>5</sup> compared to 10<sup>9</sup>).

More generally, we want to minimize the dimensionality of our DP as the dimensionality directly affects time complexity while the values in the DP do not affect time complexity.

### [F: Longest Common Subsequence][https://atcoder.jp/contests/dp/tasks/dp_f]

#### Problem Statement:

Given strings **s** and **t**, what is the longest common subsequence from both **s** and **t**

For example: 

s = "abcdefg" 

t = "agcfegf"

lcs = "acef" or l "aceg"

#### Input

1 &le; |s|, |t| &le; 3000

#### Insight

This problem seems to also want us to select the optimal combination of characters from string **s** and string **t**. 

The key insight is noticing that order matters for both **s** and **t**. This means that if we choose to use the 3<sup>rd</sup> character from s, then we give up the possibility of using 1<sup>st</sup> or 2<sup>nd</sup> character in the future. In this way, there is |s| possible ending state after the action of choosing whether to include the i<sup>th</sup> character from **t**. (The states where all characters from **s** can still be used, only 1<sup>st</sup> and above characters can be used, 2<sup>nd</sup> and above character can be used, ... so on.)

This is reminiscent of our insight from problem C Vocation. 

### [G: Longest Path][https://atcoder.jp/contests/dp/tasks/dp_g]

#### Problem Statement

Given a directed acyclic graph **G** with **N** vertices and **M** edges, what is the longest path in **G**?

Length of a path is defined as the number of edges.

#### Input

2 &le; **N** &le; 10<sup>5</sup>

1 &le; **M** &le; 10<sup>5</sup>

1 &le; **x<sub>i</sub>** , **y<sub>i</sub>** &le; **N**

(**x<sub>i</sub>**, **y<sub>i</sub>**) describe an edge from **x<sub>i</sub>** to **y<sub>i</sub>**

All (**x<sub>i</sub>**, **y<sub>i</sub>**) pairs are distinct. 

#### Insight

This problem draws on the idea of [topological ordering][https://en.wikipedia.org/wiki/Topological_sorting] which is an ordering such that "for every directed edge (u, v), from vertex u to vertex v, u comes before v in the ordering". An example use case would be in a build system, a topological ordering would let you know the order to compile your program files such that all dependency would be compiled before a file is compiled. 

Since a DAG can be sorted into a topological ordering, we can define our DP to depend on the max path length of all its children +1. 

In short, this problem becomes like the [A: Frog 1][https://atcoder.jp/contests/dp/tasks/dp_a] and [B: Frog 2][https://atcoder.jp/contests/dp/tasks/dp_b] due to DAG having a topological ordering.

### [H: Grid 1][https://atcoder.jp/contests/dp/tasks/dp_h]

#### Problem Statement

Given a grid with **H** rows and **W** columns where each cell in the grid is of type **empty**, represented by "."or a **wall** represented by "#". How many ways are there for Taro to travel from (1, 1) to (H, W) if Taro can only move right or down?

#### Input 

2 &le; **H**, **W** &le; 1000

a<sub>ij</sub> is `.` or `#`

Squares (1, 1) and (H, W) are empty squares

#### Insight 

Similar to the DAG from problem [G: Longest Path][https://atcoder.jp/contests/dp/tasks/dp_g], there is an ordering to the cells of a grid if you can only move right or down. 

`DP[i][j]` depends on `DP[i-1][j]` and `DP[i][j-1]`. 

### [I: Coins][https://atcoder.jp/contests/dp/tasks/dp_i]

#### Problem Statement

Throw **N** coins each with probability **p<sub>i</sub>** of being heads, what is the probability of having more heads than tails?

#### Input 

**N** is an odd number

1 &le; **N** &le; 2999

**p<sub>i</sub>** is a real number with 2 decimal places

0 &le; **p<sub>i</sub>** &le; 1

#### Insight

Notice the size of **N** which suggests that a time complexity of O(N<sup>2</sup>) is good enough for this one. 

Applying the idea of considering one coin toss at a time similar to [D: Knapsack 1][https://atcoder.jp/contests/dp/tasks/dp_d] and [F: Longest Common Subsequence][https://atcoder.jp/contests/dp/tasks/dp_f], we now need a way to figure out how do we consider one coin toss at a time. 

Taking more inspiration from [C: Vocation][https://atcoder.jp/contests/dp/tasks/dp_c], we can think of what are all the possible ending states after performing one action (a coin toss). (After one coin toss, there is 1 way to reach one, 1 way to reach negative 1. After 3 coin tosses, the possible states are {3, 1, -1, 3}. 

There is a pattern where the possible state is not even. More broadly, after **k** coin tosses, the maximum number of heads is at most **k**. Since **N** &le; 3000, we can store every possible ending state.

### [J: Sushi][https://atcoder.jp/contests/dp/tasks/dp_j]

#### Problem Statement

There are **N** plates with plate **i** having **a<sub>i</sub>** sushi. Taro picks a plate 1 to N with equal probability. If the chosen plate has sushi, Taro eats 1 sushi. If the chosen plate has no sushi, Taro does nothing.

What is the expected number times Taro would choose a plate until every plate is empty.

#### Input

1 &le; **N** &le; 300

1 &le; **a<sub>i</sub>** &le; 3

#### Insight

This problems boils down to how to encode the state efficiently. We could have **N** numbers with each number representing the number of sushi left on that particular plate. However, that would be an encoding with **N** dimensions, 300, which is infeasible. 

The insight then comes from finding the symmetry in the problem. In this case, the symmetry comes from the fact that every plate has equal probability of being chosen. So every plate with 3 sushi can be treated identically. 

### [K: Stones][https://atcoder.jp/contests/dp/tasks/dp_k]

#### Problem Statement

Two players are playing a game where each player can remove either **a<sub>1</sub>**, **a<sub>2</sub>**, **a<sub>3</sub>**, ..., or **a<sub>n</sub>** stones from a pile with **K** initial stones. 

Will the **first** or **second** player win assuming optimal play from both?

#### Input

1 &le; **N** &le; 100

1 &le; **K** &le; 10<sup>5</sup>

1 &le; **a<sub>1</sub>** &le; **a<sub>2</sub>**  ... **a<sub>N</sub>**

#### Insight

First, the size of **N** stands out as it suggests that it should be possible to consider every move (removing a<sub>i</sub> stones for every i). 

Second, realize that this game can be represented as a Directed Acyclic Graph (DAG).<sup>1</sup> From [G: Longest Path][https://atcoder.jp/contests/dp/tasks/dp_g], we know that a DAG can be topologically sorted and thus, fulfills the condition required for DP. 

Lastly, we just need to check if we can transition to a state where the opponent is losing. If we can, then we are winning, else we are losing.

<sup>1</sup> To convince yourself of the fact, simply realize that all moves leads to a reduction in the pile of stones. This means that it is impossible to transition from a "lower" state to a "higher" state. This means that there can never be any cycles.)

### [L: Deque][https://atcoder.jp/contests/dp/tasks/dp_l]

#### Problem Statement

Taro and Jiro are playing a game. In this game, there is a sequence **a** = (**a<sub>1</sub>**, **a<sub>2</sub>**, ... **a<sub>N</sub>**) and the players take turn remove a number from the beginning or end of the sequence and adding the number they removed to their score. 

Let **X** and **Y** be Taro and Jiro's total score at the end of the game. Taro tries to maximize **`X - Y`** while Jiro tries to minimize **`X - Y`**. 

#### Input

1 &le; **N** &le; 3000

1 &le; **a<sub>i</sub>** &le; 10<sup>9</sup>

#### Insight

Notice that we can represent the state in a few dimensions. One, whose turn it is. Two, the starting and ending position of the sub-array left. The size of this dp is 2* N<sup>2</sup>. 

Now we apply the idea of the min max algorithm which we touched on in problem K. If it's first player's turn, we try to maximize. If it's second player's turn, we minimize.

### [M: Candies][https://atcoder.jp/contests/dp/tasks/dp_m]

#### Problem Statement

How can you distribute **K** candies to **N** children where **i<sup>th</sup>** child can have between **0** and **a<sub>i</sub>** candies. There cannot be any candies left over.

#### Input

1 &le; **N** &le; 100

0 &le; **K** &le; 10<sup>5</sup>

0 &le; **a<sub>i</sub>** &le; **K**

#### Insight

From counting, we know that we can consider each event independently and often add the possibilities up or multiply them together.

In this case, since we are partitioning. We want to add up the possibilities if we distribute 0 candy to children i,1 candy to children i, 2 candy, ...

Summing this will take O(n) time but we since we are repeated doing range sum, we can use a prefix sum.

### [N: Slimes][https://atcoder.jp/contests/dp/tasks/dp_n]

#### Problem Statement

There are **N** slimes which can be merged with adjacent slimes. Each slime has a size of **a<sub>i</sub>** and the cost of merging two slimes is **x + y** where **x** is the cost of the left slime and **y** is the cost of the right slime.

What is the minimum cost to merge all **N** slime?

#### Input

2 &le; **N** &le; 400

1 &le; **a<sub>i</sub>** &le; 10<sup>9</sup>

#### Insight

The "action" we do in this problem is merging. From that, we can see that we can use dp to solve the sub problem of optimal left and optimal right slime.

 
