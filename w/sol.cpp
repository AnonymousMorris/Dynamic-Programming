#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct Node {
    int l, r;
    ll val, tag;
    Node *lc, *rc;

    Node (int left, int right) {
        l = left;
        r = right;
        val = 0;
        tag = 0;
        if (l == r) {
            lc = rc = nullptr;
        }
        else {
            int mid = (left + right) / 2;
            lc = new Node(left, mid);
            rc = new Node(mid+1, right);
        }
    }

    void range_add(int left, int right, ll value) {
        // completely outside
        if (left > r || right < l) {
            return;
        }
        // completely inside
        if (left <= l && right >= r) {
            apply_tag(value);
            return;
        }
        // partially inside
        lc -> range_add(left, right, value);
        rc -> range_add(left, right, value);
        val = max_child();
    }

    ll range_query(int left, int right, ll tag_val) {
        // completely outside
        if (left > r || right < l) {
            apply_tag(tag_val);
            return LONG_LONG_MIN;
        }
        // completely inside
        if (left <= l && right >= r) {
            apply_tag(tag_val);
            return val + tag;
        }
        // partially inside
        int new_tag_val = tag_val + tag;
        tag = 0;

        ll ans =  max(lc -> range_query(left, right, new_tag_val) 
            , rc -> range_query(left, right, new_tag_val));
        val = max_child();
        return ans;
    }

    void set(int idx, ll value) {
        ll idx_val = range_query(idx, idx, 0);
        range_add(idx, idx, -idx_val);
        range_add(idx, idx, value);
        assert(idx >= l && idx <= r);
        string msg = "expected: " + to_string(idx_val) + " got: " + to_string(range_query(idx, idx, 0));
        if (range_query(idx, idx, 0) != value)
            cerr <<  msg;
        assert(range_query(idx, idx, 0) == value);
    }
    

    void apply_tag(ll tag_val) {
        if (l == r) 
            val += tag_val;
        else 
            tag += tag_val;
    }

    ll max_child() {
        if (l == r) 
            return 0;

        ll l_val = lc->val + lc->tag;
        ll r_val = rc->val + rc->tag;
        return max(l_val, r_val);
    }

    void print(int depth) {
        indent(depth);
        cout << "(" << l << "," << r << ": v=" << val << ", tag=" << tag << "\n";
        if (lc != nullptr)
            lc -> print(++depth);
        if (rc != nullptr)
            rc -> print(depth);
    }
    
    void indent(int cnt) {
        for (int i = 0; i < cnt; i++) {
            cout << "   ";
        }
    }
};


struct range {
    int l, r, v;
    void print() {
        cout << "l: " << l << " r: " << r << endl;
    }
};

void print_dp(Node tree) {
    for(int i = 0; i <= tree.r; i++) {
        cout << i << ": " << tree.range_query(i, i, 0) << endl;
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<range> ranges(m);
    for (auto &i: ranges) {
        cin >> i.l >> i.r >> i.v;
    }
    vector<range> by_end(ranges);
    sort(by_end.begin(), by_end.end(), [](range a, range b) {
            return a.r < b.r;
    });

    Node dp = Node(0, n);
    for (auto i : ranges) {
        dp.range_add(i.l, i.r, -i.v);
    }
    int by_end_ptr = 0;

    for (int i = 1; i <= n; i++) {
        while (by_end_ptr < m && by_end[by_end_ptr].r < i) {
            range cur = by_end[by_end_ptr];
            dp.range_add(cur.l, cur.r, cur.v);
            by_end_ptr++;
        }

        dp.set(i, dp.range_query(0, i-1, 0));
    }
    while (by_end_ptr < m && by_end[by_end_ptr].r <= n) {
        range cur = by_end[by_end_ptr];
        dp.range_add(cur.l, cur.r, cur.v);
        by_end_ptr++;
    }

    cout << dp.range_query(0, n, 0);
}
