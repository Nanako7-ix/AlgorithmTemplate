#include <bits/stdc++.h>

// f(a[fa], a[son]) = true
template<typename Iterator, typename Func, typename = std::_RequireInputIter<Iterator>>
auto CartesianTree(const Iterator& l, const Iterator& r, Func&& f) {
    int n = r - l;
    std::vector<int> ls(n + 1), rs(n + 1), fa(n + 1);
    std::vector<int> stk;

    auto a = [&](int p) {
        return *(l + p - 1);
    };

    for(int i = 1; i <= n; ++i) {
        while(!stk.empty() && f(a(i), a(stk.back()))) {
            ls[i] = stk.back();
            stk.pop_back();
        }
        fa[ls[i]] = i;
        if(!stk.empty()) {
            rs[stk.back()] = i;
            fa[i] = stk.back();
        }
        stk.push_back(i);
    }

    return std::tuple {
        stk[0],
        std::move(ls),
        std::move(rs),
        std::move(fa)
    };
}
