#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct Node {
    int l, r, val, tag;
    Node *lc, *rc;
    Node (int bl, int br) {
        l = bl, r = br, val = 0, tag = 0;
        int mid = (bl + br) >> 1;
        if (bl == br) lc = rc = nullptr;
        else lc = new Node(bl, mid), rc = new Node(mid + 1, br); 
    }
    
    ~Node() {
        delete lc;
        delete rc;
    }

    ll add(int bl, int br, int val) {
        // break condition
        if (r < bl || br < l) return val;
        // tag condition
        if (bl <= l && r <= br) {
            putTag(val);
            return val + tag;
        }
        return lc -> add(bl, br, val) + rc -> add(bl, br, val);
    }

    int qry(int ql, int qr, int tagVal) {
        // break condition
        if (ql > r || qr < l) {
            putTag(tagVal);
            return 0;
        }
        // tag condition
        if (ql >= l && qr <= r) {
            putTag(tagVal);
            return val;
        }
        tagVal += getTag();
        val = max(lc -> qry(ql, qr, tagVal), rc -> qry(ql, qr, tagVal));
        return val;
    }

    void putTag (int tagVal) {
        if (l == r) val += tagVal;
        else tag += tagVal;
    }

    int getTag() {
        int tmp = tag;
        tag = 0;
        return tmp;
    }

    void print() {
        if (l == r) cout << val;
        else {
            cout << " (";
            lc -> print();
            cout << "[";
            cout << val;
            cout << ", ";
            cout << tag;
            cout << "]";
            rc -> print();
            cout << ") ";
        }
    }
};

// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<tuple<int , int, int>> range(m);
//     vector<int>dp(n);
//     for (int i = 0; i < m; i++) {
//         cin >> get<0>(range[i]) >> get<1>(range[i]) >> get<2>(range[i]);
//     }
//     sort(range.begin(), range.end());
//
//     dp[0] = 
//     for (int i = 0; i < n; i++) {
//         
//     }
//
// }
//
int main() {
    Node *seg = new Node(0, 10);
    seg->add(0, 3, 5);
    cout << seg -> qry(3, 3, 0) << endl;
    seg -> print();
    seg -> add(3, 5, 3);
    cout << seg -> qry(1, 10, 0) << endl;
    seg -> print();
}
