#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

// template<typename T>
// struct SparseTable {
//   std::vector<std::vector<T>> st;
//   std::function<T(T, T)> op;

//   SparseTable() = default;

//   template<typename Iter, typename Func, typename = std::_RequireInputIter<Iter>>
//   SparseTable(const Iter& l, const Iter& r, Func&& op) : op(std::forward<Func>(op)) {
//     init(r - l, [&](int p) { return *(l + p - 1); });
//   }

//   template<typename Init, typename Func>
//   SparseTable(int n, Init&& f, Func&& op) : op(std::forward<Func>(op)) {
//     init(n, f);
//   }
  
//   template<typename Func>
//   void set(Func&& op) {
//     this -> op = std::forward<Func>(op);
//   }

//   template<typename Init>
//   void init(int n, Init&& f) {
//     st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
//     for (int i = 1; i <= n; ++i) {
//       st[0][i] = f(i);
//     }
//     for (int i = 1; i <= std::__lg(n); ++i) {
//       for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
//         st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
//       }
//     }
//   }

//   T operator()(int l, int r) {
//     assert(l <= r);
//     int k = std::__lg(r - l + 1);
//     return op(st[k][l], st[k][r - (1 << k) + 1]);
//   }
// };

template<typename T, typename Func>
struct SparseTable {
  std::vector<std::vector<T>> st;
  Func op;
  SparseTable() {
    cout << op(1, 2);
  }
};

void Thephix() {
  array<SparseTable<int, decltype([&](int x, int y) { return min(x, y); })>, 2> {};
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}