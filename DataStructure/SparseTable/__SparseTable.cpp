#include <bits/stdc++.h>

template<typename T, typename Func>
struct SparseTable {
	int n;
	Func op;
	std::vector<std::vector<T>> st;

	SparseTable () = default;

	SparseTable (int n) {
		init(n);
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	SparseTable (const Iter& l, const Iter& r, Func&& f)
	: op(std::forward<Func> (f)) { init(l, r); }

	template<typename Init, typename Func>
	SparseTable (int n, Init&& g, Func&& f)
	: op(std::forward<Func> (f)) { init(n, g); }
	
	void init(int n) {
		this -> n = n;
		st.assign(std::__lg(n) / 2 + 1, std::vector<T> (n + 1));
	}
	
	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init(const Iter& l, const Iter& r) {
		init(r - l, [&](int p) { return *(l + p - 1); });
	}

	template<typename Init>
	void init(int n, Init&& f) {
		init(n);
		for (int i = 1; i <= n; ++i) {
			st[0][i] = f(i);
		}
		build();
	}
	
	void build() {
		for (int i = 1; i <= std::__lg(n) / 2; ++i) {
			for (int j = 1; j + (1 << (i << 1)) - 1 <= n; ++j) {
				st[i][j] = op(
					op(st[i - 1][j + 0 * (1 << ((i - 1) << 1))], st[i - 1][j + 1 * (1 << ((i - 1) << 1))]),
					op(st[i - 1][j + 2 * (1 << ((i - 1) << 1))], st[i - 1][j + 3 * (1 << ((i - 1) << 1))])
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

template<typename Init, typename Func>
SparseTable(int, Init&&, Func&&) ->
SparseTable<std::invoke_result_t<Init, int>, Func>;

template<typename Iter, typename Func>
SparseTable (const Iter&, const Iter&, Func&&) ->
SparseTable<typename std::iterator_traits<Iter>::value_type, Func>;
