#include<bits/stdc++.h>

template<std::unsigned_integral U>
struct Bitset {
	struct Proxy {
		U& x;
		int p;
		Proxy(U& x, int p) : x(x), p(p) {}
		Proxy& operator=(bool v) {
			x &= ~(U(1) << p);
			if (v) x |= U(1) << p;
			return *this;
		}
		Proxy& operator=(const Proxy& v) {
			return *this = bool(v);
		}
		operator bool() const {
			return x >> p & 1;
		}
		void filp() { x ^= U(1) << p; }
	};

	int n;
	std::vector<U> d;
	static constexpr int B = sizeof(U) * 8;

	Bitset(int n = 0) : n(n) {
		int len = (n + B - 1) / B;
		d.assign(len, 0);
	}

	void trim() {
		int r = n % B;
		if (r) d.back() &= (U(1) << r) - 1;
	}

	void resize(int k) {
		int len = (k + B - 1) / B;
		d.resize(len);
		n = k;
		trim();
	}

	void set() {
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] = U(-1);
		}
		trim();
	}

	void reset() {
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] = U(0);
		}
	}

	void flip() {
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] = ~d[i];
		}
		trim();
	}

	Proxy operator[] (int p) {
		assert(0 <= p && p < n);
		return Proxy(d[p / B], p % B);
	}

	const Proxy operator[] (int p) const {
		assert(0 <= p && p < n);
		return Proxy(d[p / B], p % B);
	}

	Bitset operator~() const {
		Bitset res(*this);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			res.d[i] = ~d[i];
		}
		res.trim();
		return res;
	}

	Bitset& operator&=(const Bitset& o) & {
		assert(n == o.n);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] &= o.d[i];
		}
		return *this;
	}

	Bitset& operator|=(const Bitset& o) & {
		assert(n == o.n);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] |= o.d[i];
		}
		return *this;
	}

	Bitset& operator^=(const Bitset& o) & {
		assert(n == o.n);
		int len = d.size();
		for (int i = 0; i < len; ++i) {
			d[i] ^= o.d[i];
		}
		return *this;
	}

	Bitset& operator<<=(const int& k) & {
		int len = d.size(), x = k / B, y = k % B, z = B - y;
		for (int i = d.size() - 1; i > x; --i) {
			d[i] = d[i - x] << y | d[i - x - 1] >> z;
		}
		if (x < len) d[x] = d[0] << y;
		for (int i = 0; i < std::min(x, len); ++i) {
			d[i] = 0;
		}
		return *this;
	}

	Bitset& operator>>=(const int& k) & {
		int len = d.size(), x = k / B, y = k % B, z = B - y;
		for (int i = 0; i < len - x - 1; ++i) {
			d[i] = d[i + x] >> y | d[i + x + 1] << z;
		}
		if (x <= len - 1) d[len - x - 1] = d[len] >> y;
		for (int i = std::max(len - x, 0); i < len; ++i) {
			d[i] = 0;
		}
		return *this;
	}

	friend Bitset operator&(Bitset x, const Bitset& y) { x &= y; return x; }
	friend Bitset operator|(Bitset x, const Bitset& y) { x |= y; return x; }
	friend Bitset operator^(Bitset x, const Bitset& y) { x ^= y; return x; }
	friend Bitset operator<<(Bitset x, const int& k) { x <<= k; return x; }
	friend Bitset operator>>(Bitset x, const int& k) { x >>= k; return x; }

	int count() const {
		int ans = 0, len = d.size();
		for (int i = 0; i < len; ++i) {
			ans += std::popcount(d[i]);
		}
		return ans;
	}

	int count(int l, int r) const {
		return (*this >> l).count() - (*this >> (r + 1)).count();
	}

	bool any() const { return count() != 0; }
	bool all() const { return count() == n; }
};
