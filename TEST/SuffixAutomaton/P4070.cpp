/**
 * Author:  Thephix
 * Created: 2025/06/06 17:44:28
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using f64 = double;
using f128 = __float128;
using namespace std;

#include <bits/stdc++.h>

struct SuffixAutomaton {
    struct Node {
        int len;
        int link;
        std::map<int, int> next;
        Node() : len(), link(), next() {}
    };

    i64 substr;
    std::vector<Node> t;

    SuffixAutomaton () { init(); }

    void init() {
        t.assign(2, Node {});
        t[0].len = -1;
        substr = 0;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int extend(int p, int c) {
        if (t[p].next.contains(c) && t[p].next.at(c)) {
            int q = t[p].next.at(c);
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next.contains(c) && t[p].next.at(c) == q) {
                t[p].next.at(c) = r;
                p = t[p].link;
            }
            return r;
        }

        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next.contains(c) || !t[p].next.at(c)) {
            t[p].next[c] = cur;
            p = t[p].link;
        }

        t[cur].link = p == 0 ? 1 : extend(p, c);
        substr += t[cur].len - t[t[cur].link].len;
        return cur;
    }

    int len(int p) {
        return t[p].len;
    }

    int link(int p) {
        return t[p].link;
    }

    int next(int p, int x) {
        return t[p].next.contains(x) ? t[p].next[x] : 0;
    }
    
    int size() {
        return t.size();
    }

    i64 count () {
        return substr;
    }
};

void solve() {
    int n, p = 1;
    cin >> n;
    SuffixAutomaton SAM;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        p = SAM.extend(p, x);
        cout << SAM.count() << "\n";
    }
}

signed main() {
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T = 1;
    // std::cin >> T;

    while (T--) {
        solve ();
    }

    return 0;
}