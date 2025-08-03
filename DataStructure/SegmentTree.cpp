#include <bits/stdc++.h>

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    
    SegmentTree() = default;
    
    SegmentTree(int n) { init(n); }
    
    void init(int n) {
        init(n, [](int p) { return Info{}; });
    }
    
    template<typename Func>
    SegmentTree(int n, Func&& f) { init(n, f); }
    
    template<typename Func>
    void init(int n, Func&& f) {
        this -> n = n;
        info.assign(4 << __lg(n), Info {});
        build(1, 1, n, f);
    }
    
    void pull(int u) {
        info[u] = info[ls] + info[rs];
    }
    
    template<typename Func>
    void build(int u, int l, int r, Func&& f) {
        if (l == r) {
            info[u] = f(l);
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, f);
        build(rs, m + 1, r, f);
        pull(u);
    }
    
    template<typename Func>
    void modify(int p, Func&& op, int u, int l, int r) {
        if (l == r) {
            op(info[u]);
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m) {
            modify(p, op, ls, l, m);
        } else {
            modify(p, op, rs, m + 1, r);
        }
        pull(u);
    }
    template<typename Func>
    void modify(int p, Func&& op) {
        modify(p, op, 1, 1, n);
    }
    
    Info query(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            return info[u];
        }
        int m = (l + r) >> 1;
        if (R <= m) {
            return query(L, R, ls, l, m);
        } else if (L > m) {
            return query(L, R, rs, m + 1, r);
        } else {
            return query(L, R, ls, l, m) + query(L, R, rs, m + 1, r);
        }
    }
    Info query(int l, int r) {
        assert(l <= r);
        return query(l, r, 1, 1, n);
    }
    
    template<typename Func>
    pair<int, bool> FindL(int L, int R, Func&& f, int u, int l, int r) {
        if (l > R || r < L || !f(info[u])) return {0, 0};
        if (l == r) return {l, 1};
        int m = (l + r) >> 1;
        auto [p, get] = FindL(L, R, f, ls, l, m);
        if (get) return { p, get };
        return FindL(L, R, f, rs, m + 1, r);
    }
    template<typename Func>
    auto FindL(int l, int r, Func&& f) {
        assert(l <= r);
        return FindL(l, r, f, 1, 1, n);
    }
    
    template<typename Func>
    pair<int, bool> FindR(int L, int R, Func&& f, int u, int l, int r) {
        if (l > R || r < L || !f(info[u])) return {0, 0};
        if (l == r) return {l, 1};
        int m = (l + r) >> 1;
        auto [p, get] = FindR(L, R, f, rs, m + 1, r);
        if (get) return {p, get};
        return FindR(L, R, f, ls, l, m);
    }
    template<typename Func>
    auto FindR(int l, int r, Func&& f) {
        assert(l <= r);
        return FindR(l, r, f, 1, 1, n);
    }
};
#undef ls
#undef rs
