#include <bits/stdc++.h>
using namespace std;

struct PAM {
    static constexpr int N = 26;
    struct Node {
        int len, fail;
        std::array<int, N> next;
        Node() : len(0), fail(0), next{} {}
    };
    
    int cur;
    std::vector<int> s;
    std::vector<Node> t;
    
    PAM(int n = 0) {
        s.reserve(n), t.reserve(n + 2);
        t.assign(2, Node());
        t[t[cur = 0].fail = 1].len = -1;
    }
    
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    int append(int ch) {
        int n = s.size();
        s.push_back(ch);

        auto get = [&](int p) {
            while (n - t[p].len - 1 < 0 || ch != s[n - t[p].len - 1]) {
                p = t[p].fail;
            }
            return p;
        };

        int p = get(cur);
        if (t[p].next[ch] == 0) {
            cur = newNode();
            t[cur].len = t[p].len + 2;
            t[p].next[ch] = cur;
            if (t[cur].len != 1) {
                t[cur].fail = t[get(t[p].fail)].next[ch];
            }
        }
        return cur = t[p].next[ch];
    }

    int append(char ch, char offset = 'a') {
        return append(ch - offset);
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int fail(int p) {
        return t[p].fail;
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int size() {
        return t.size();
    }
};

int main () {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s;
    cin >> s;

    int n = s.size(), last = 0;
    PAM pam(n);
    vector<int> dep(n + 2);
    for (int i = 0; i < n; ++i) {
        s[i] = (s[i] - 'a' + last) % 26 + 'a';
        int p = pam.append(s[i]);
        dep[p] = dep[pam.fail(p)] + 1;
        cout << (last = dep[p]) << " \n"[i == n - 1];
    }

    return 0;
}
