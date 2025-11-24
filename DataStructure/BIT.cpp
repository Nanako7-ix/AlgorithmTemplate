template<typename T>
struct BIT {
	int n;
	std::vector<T> tr;
	constexpr int lowbit(int x) { return ; }

	BIT () = default;
	BIT (int n, const T& e = T()) { init(n, e); }

	template<typename Array> BIT (int n, Array&& a) { init(n, a); }

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	BIT (const Iter& l, const Iter& r) { init(l, r); }

	void init (int n, const T& e = T()) {
		init(n, [&](int) { return e; });
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init (const Iter& l, const Iter& r) {
		init(r - l, [&](int p) { return l[p - 1]; });
	}

	template<typename Array>
	void init (int n, Array&& a) {
		this -> n = n;
		tr.assign(n + 1, T {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += a(i);
			if(i + (i & -i) <= n) {
				tr[i + (i & -i)] += tr[i];
			}
		}
	}

	void modify (int p, const T& v) {
		for (; p <= n; p += p & -p) tr[p] += v;
	}

	T query (int p) const {
		T res = T();
		for (; p; p -= p & -p) res += tr[p];
		return res;
	}

	T query (int l, int r) const {
		return query(r) - query(l - 1);
	}

	int lower_bound (T k) const {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] < k) {
				k -= tr[x += i];
			}
		}
		return x + 1;
	}

	int upper_bound (T k) const {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] <= k) {
				k -= tr[x += i];
			}
		}
		return x + 1;
	}
};
