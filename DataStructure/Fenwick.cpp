template<typename T, int Base = 1>
struct BIT {
	constexpr static int offset = 1 - Base;
	int n;
	std::vector<T> tr;
	constexpr int lowbit(int x) { return x & -x; }

	BIT () = default;

	BIT (int n, const T& e = T()) { init(n, e); }

	template<typename Func>
	BIT (int n, Func&& f) { init(n, f); }

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	BIT (const Iter& l, const Iter& r) { init(l, r); }

	void init (int n, const T& e = T()) {
		init(n, [&](int) { return e; });
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init (const Iter& l, const Iter& r) {
		init(r - l, [&](int p) { return l[p - 1]; });
	}

	template<typename Func>
	void init (int n, Func&& f) {
		this -> n = n;
		tr.assign(n + 1, T {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += f(i);
			if(i + lowbit(i) <= n) {
				tr[i + lowbit(i)] += tr[i];
			}
		}
	}

	void modify (int p, const T& v) {
		p += offset;
		for(; p <= n; p += lowbit(p)) {
			tr[p] += v;
		}
	}

	T query (int p) {
		p += offset;
		T res {};
		for(; p; p -= lowbit(p)) {
			res += tr[p];
		}
		return res;
	}

	T query (int l, int r) {
		return query(r) - query(l - 1);
	}

	int lower_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] < k) {
				k -= tr[x += i];
			}
		}
		return x + 1 - offset;
	}

	int upper_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] <= k) {
				k -= tr[x += i];
			}
		}
		return x + 1 - offset;
	}
};
