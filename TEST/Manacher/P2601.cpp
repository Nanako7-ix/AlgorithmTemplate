#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename Func>
std::vector<int> Manacher(int n, Func&& op, const int def = '#') {
	n = n << 1 | 1;
	std::vector<int> s(n + 1);
	for (int i = 1; i <= n; ++i) {
		s[i] = i % 2 == 1 ? def : op(i / 2);
	}

	std::vector<int> d(n + 1);
	for (int i = 1, j = 1; i <= n; ++i) {
		d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
		while (i + d[i] <= n && i - d[i] >= 1 && s[i + d[i]] == s[i - d[i]]) ++d[i];
		if (i + d[i] > j + d[j]) j = i;
	}
	return d;
}

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

struct Min {
	int operator()(int x, int y) {
		return min(x, y);
	}
};

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n + 1, vector<int> (m + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	int N = n << 1 | 1, M = m << 1 | 1;
	vector row(M + 1, SparseTable<int, Min>());
	vector col(M + 1, SparseTable<int, Min>());
	for (int i = 1; i <= n; ++i) {
		auto d = Manacher(m, [&](int p) { return a[i][p]; }, 0);
		for (int j = 1; j <= M; ++j) {
			row[j].st[0][i] = d[j];
		}
	}
	for (int i = 1; i <= m; ++i) {
		auto d = Manacher(n, [&](int p) { return a[p][i]; }, 0);
		for (int j = 1; j <= N; ++j) {
			col[j].st[0][i] = d[j];
		}
	}

	for (int i = 1; i <= M; ++i) {
		row[i].build();
	}
	for (int i = 1; i <= N; ++i) {
		col[i].build();
	}

	i64 ans = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1 + !(i & 1); j <= M; j += 2) {
			int l = 1, r = min({i, j, N - i + 1, M - j + 1}), res = -1;
			auto check = [&](int x) -> bool {
				int ok = 1;
				ok &= (i - x) / 2 + 1 <= (i + x - 1) / 2 ? row[j]((i - x) / 2 + 1, (i + x - 1) / 2) >= x : 1;
				ok &= (j - x) / 2 + 1 <= (j + x - 1) / 2 ? col[i]((j - x) / 2 + 1, (j + x - 1) / 2) >= x : 1;
				return ok;
			};
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (check(mid)) {
					res = mid, l = mid + 1;
				} else r = mid - 1;
			}
			assert(res != -1);
			ans += res / 2;
		}
	}
	cout << ans << "\n";
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
