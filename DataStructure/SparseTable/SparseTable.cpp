#include <bits/stdc++.h>

template<typename T, typename Func>
struct SparseTable {
    int n;
    Func op;
    std::vector<std::vector<T>> st;

    SparseTable () = default;

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SparseTable (const Iterator& l, const Iterator& r, Func&& f) : n(r - l), op(f) {
        st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
        for (int i = 1; i <= n; ++i) st[0][i] = *(l + i - 1);
        build();
    }
    
    template<typename Init>
    SparseTable (int n, Init&& op, Func&& f) : n(n), op(f) {
        st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
        for (int i = 1; i <= n; ++i) st[0][i] = op(i);
        build();
    }

    void build() {
        for (int i = 1; i <= std::__lg(n); ++i) {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T operator () (int l, int r) {
        assert(l <= r);
        int k = std::__lg(r - l + 1);
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

template<typename Iterator, typename Func>
SparseTable (const Iterator&, const Iterator&, Func&&) ->
SparseTable<typename std::iterator_traits<Iterator>::value_type, Func>;
