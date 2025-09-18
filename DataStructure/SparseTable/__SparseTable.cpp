#include <bits/stdc++.h>

template<typename T, typename Func>
struct SparseTable {
	int n;
	Func op;
	std::vector<std::vector<T>> st;

	SparseTable () = default;

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	SparseTable (const Iter& l, const Iter& r, Func&& f) : n(r - l), op(f) {
		st.assign(std::__lg(n) / 2 + 1, std::vector<T> (n + 1));
		for (int i = 1; i <= n; ++i) {
			st[0][i] = l[i - 1];
		}
		for (int i = 1; i <= std::__lg(n) / 2; ++i) {
			for (int j = 1; j + (1 << (i << 1)) - 1 <= n; ++j) {
				st[i][j] = op(
					op(
						st[i - 1][j + (0 << ((i - 1) << 1))],
						st[i - 1][j + (1 << ((i - 1) << 1))]
					),
					op(
						st[i - 1][j + (2 << ((i - 1) << 1))],
						st[i - 1][j + (3 << ((i - 1) << 1))]
					)
				);
			}
		}
	}

	T operator () (int l, int r) {
		assert(l <= r);
		int k = std::__lg(r - l + 1) / 2;
		if ((2 << (k << 1)) >= r - l + 1) {
			return op(st[k][l], st[k][r - (1 << (k << 1)) + 1]);
		} else {
			return op(st[k][l], operator()(l + (1 << (k << 1)), r));
		}
	}
};

template<typename Iter, typename Func>
SparseTable (const Iter&, const Iter&, Func&&) ->
SparseTable<typename std::iterator_traits<Iter>::value_type, Func>;
