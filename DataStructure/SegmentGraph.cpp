#include <bits/stdc++.h>

// 线段树优化建图, 处理区间连边问题
// [l, r] -> v
#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Func>
struct SegmentGraph {
    int n;
    std::vector<int> p;
    Func add;
    
    SegmentGraph() = default;
    
    SegmentGraph(int n, Func&& F) : add(F) {
        this -> n = n;
        p.assign(n + 1, 0);
        build(1, 1, n);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            p[l] = u;
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m);
        build(rs, m + 1, r);
        add(u, ls), add(u, rs);
    }

    void link(int L, int R, int v, int u, int l, int r) {
        if (L <= l && r <= R) {
            return void(add(p[v], u));
        }
        int m = (l + r) >> 1;
        if (L <= m) link(L, R, v, ls, l, m);
        if (R > m)  link(L, R, v, rs, m + 1, r);
    }

    void link(int v, int l, int r) {
        link(l, r, v, 1, 1, n);
    }
};
#undef ls
#undef rs

// v -> [l, r]
// struct SegmentGraph {
//     int n;
//     std::vector<int> p;
//     std::vector<std::vector<int>> adj;
    
//     SegmentGraph() = default;
    
//     SegmentGraph(int n) {
//         init(n);
//     }

//     void init(int n) {
//         this -> n = n;
//         p.assign(n + 1, 0);
//         adj.assign(4 << std::__lg(n), {});
//         build(1, 1, n);
//     }

//     void build(int u, int l, int r) {
//         if (l == r) {
//             p[l] = u;
//             return;
//         }
//         adj[u].push_back(ls);
//         adj[u].push_back(rs);

//         int m = (l + r) >> 1;
//         build(ls, l, m);
//         build(rs, m + 1, r);
//     }

//     void link(int L, int R, int v, int u, int l, int r) {
//         if (L <= l && r <= R) {
//             adj[p[v]].push_back(u);
//             return;
//         }
//         int m = (l + r) >> 1;
//         if (L <= m) link(L, R, v, ls, l, m);
//         if (R > m)  link(L, R, v, rs, m + 1, r);
//     }

//     void link(int v, int l, int r) {
//         link(l, r, v, 1, 1, n);
//     }

//     int size() {
//         return 4 << std::__lg(n);
//     }
// };

// TODO
// [x, y] -> [l, r]
// struct SegmentGraph {
//     int n;
//     std::vector<std::vector<int>> adj;
//     SegmentGraph() = default;
    
//     SegmentGraph(int n) {
//         init(n);
//     }
    
//     void init(int n) {
//         this -> n = n;
        
//     }
    
//     int Node() {
//         adj.push_back({});
//         return adj.size() - 1;
//     }
// };
