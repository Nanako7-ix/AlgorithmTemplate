#include <bits/stdc++.h>

using u32 = unsigned int;
using i64  = long long;
using u64  = unsigned long long;
using u128 = unsigned __int128;

template<typename Z>
constexpr Z PrimitiveRoot() {
	u64 P = Z::mod(); Z i = 2;
	for (; i.pow((P - 1) / 2) == 1; i += 1);
	return i.pow((P - 1) >> std::countr_zero(P - 1));
}

template<typename Z>
struct Poly : public std::vector<Z> {
	Poly() : std::vector<Z> () {}
	explicit constexpr Poly(int n) : std::vector<Z> (n) {}
	explicit constexpr Poly(const std::vector<Z>& a) : std::vector<Z> (a) {}
	explicit Poly(const std::initializer_list<Z>& a) : std::vector<Z> (a) {}

	template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
	explicit constexpr Poly(Iterator l, Iterator r) : std::vector<Z> (l, r) {}
			
	template<typename Func>
	explicit constexpr Poly(int n, Func&& f) : std::vector<Z> (n) {
		for (int i = 0; i < n; i++) {
			(*this)[i] = f(i);
		}
	}
			
	constexpr Poly trunc(int k) const {
		assert(k >= 0);
		Poly f(*this);
		f.resize(k);
		return f;
	}

	constexpr friend Poly operator<<(const Poly& p, int k) {
		assert(k >= 0);
		if (k < (int) p.size()) {
			return Poly(p.begin() + k, p.end());
		}
		return Poly();
	}

	constexpr friend Poly operator>>(const Poly& p, int k) {
		assert(k >= 0);
		Poly f(p);
		f.insert(f.begin(), k, 0);
		return f;
	}

	constexpr friend Poly operator+(const Poly& f, const Poly& g) {
		int n = f.size(), m = g.size();
		Poly h(std::max(n, m));
		for (int i = 0; i < n; i++) {
			h[i] += f[i];
		}
		for (int i = 0; i < m; ++i) {
			h[i] += g[i];
		}
		return h;
	}

	constexpr friend Poly operator-(const Poly& f, const Poly& g) {
		int n = f.size(), m = g.size();
		Poly h(std::max(n, m));
		for (int i = 0; i < n; i++) {
			h[i] += f[i];
		}
		for (int i = 0; i < m; ++i) {
			h[i] -= g[i];
		}
		return h;
	}

	constexpr Poly operator-() const {
		Poly f(*this);
		for (auto& x : f) x = -x;
		return f;
	}

	friend constexpr Poly operator* (Poly f, const Z& k) {
		int n = f.size();
		for (int i = 0; i < n; ++i) {
			f[i] *= k;
		}
		return f;
	}

	friend constexpr Poly operator* (const Z& k, Poly f) {
		int n = f.size();
		for (int i = 0; i < n; ++i) {
			f[i] *= k;
		}
		return f;
	}

	friend constexpr Poly operator/ (Poly f, const Z& k) {
		int n = f.size();
		for (int i = 0; i < n; ++i) {
			f[i] /= k;
		}
		return f;
	}

	friend constexpr Poly operator* (Poly a, Poly b) {
		int n = a.size(), m = b.size();
		if (n == 0 || m == 0) return Poly();
		if (n < m) std::swap(a, b), std::swap(n, m);

		if (m < 128) {
			Poly f(n + m - 1);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					f[i + j] += a[i] * b[j];
				}
			}
			return f;
		}

		int tot = n + m - 1;
		int k = std::__lg(tot - 1);
		n = 1 << (k + 1);

		std::vector<int> rev(n);
		for (int i = 0; i < n; ++i) {
			rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
		}
		if ((int) roots.size() < n) {
			int k = std::countr_zero(roots.size());
			roots.resize(n);
			for (; (1 << k) < n; ++k) {
				auto e = g.pow((Z::mod() - 1) >> (k + 1));
				for (int i = 1 << (k - 1); i < (1 << k); ++i) {
					roots[i << 1] = roots[i];
					roots[i << 1 | 1] = roots[i] * e;
				}
			}
		}

		auto dft = [&](Poly& f) {
			for (int i = 0; i < n; ++i) {
				if (i < rev[i]) std::swap(f[i], f[rev[i]]);
			}
			for (int i = 1; i < n; i <<= 1) {
				for (int j = 0; j < n; j += 2 * i) {
					for (int k = 0; k < i; ++k) {
						Z fx = f[j + k];
						Z fy = f[i + j + k] * roots[i + k];
						f[j + k] = fx + fy;
						f[i + j + k] = fx - fy;
					}
				}
			}
		};
		
		a.resize(n), b.resize(n);
		dft(a), dft(b);
		for (int i = 0; i < n; ++i) {
			a[i] *= b[i];
		}
		std::reverse(a.begin() + 1, a.end());
		dft(a);
		a.resize(tot);
		Z inv = Z(1 - Z::mod()) / n;
		for (int i = 0; i < tot; ++i) {
			a[i] *= inv;
		}
		return a;
	}

	constexpr Poly derivative() const {
		int n = this->size();
		if (n <= 1) return Poly();
		Poly f(n - 1);
		for (int i = 1; i < n; ++i) {
			f[i - 1] = i * (*this)[i];
		}
		return f;
	}

	constexpr Poly integral() const {
		int n = this->size();
		Poly f(n + 1);
		for (int i = 0; i < n; ++i) {
			f[i + 1] = (*this)[i] / (i + 1);
		}
		return f;
	}

	constexpr Poly inv(int m) const {
		Poly f { (*this)[0].inv() };
		int k = 1;
		while (k < m) {
			k <<= 1;
			f = f * (Poly {2} - trunc(k) * f).trunc(k);
		}
		return f;
	}

	constexpr Poly log(int m) const {
		return (derivative() * inv(m)).integral().trunc(m);
	}

	constexpr Poly exp(int m) const {
		Poly f {1};
		int k = 1;
		while (k < m) {
			k *= 2;
			f = (f * (Poly {1} - f.log(k) + trunc(k))).trunc(k);
		}
		return f;
	}

	constexpr Poly pow(int k, int m) const {
		
	}
private:
	static constexpr Z g = PrimitiveRoot<Z>();
	static std::vector<Z> roots;
};

template<typename Z> std::vector<Z> Poly<Z>::roots {0, 1};

template<u32 Mod> constexpr u32 mulMod(u32 a, u32 b) { return static_cast<u64> (a) * b % Mod; }
template<u64 Mod> constexpr u64 mulMod(u64 a, u64 b) { return static_cast<u128>(a) * b % Mod; }

template<std::unsigned_integral U, U Mod, typename S = std::make_signed_t<U>>
struct ModInt {
public:
	constexpr ModInt() : x(0) {}
	template<std::unsigned_integral T> constexpr ModInt(T v) : x(v % Mod) {}
	template<std::signed_integral T> constexpr ModInt(T v) { S t = v % S(Mod); x = t < 0 ? t + Mod : t; }
	constexpr U val() const { return x; }
	constexpr static int mod() { return Mod; }
	constexpr ModInt operator-() const { return x == 0 ? 0 : Mod - x; }
	constexpr ModInt inv() const { return pow(Mod - 2); }
	constexpr ModInt& operator+=(const ModInt& rhs) & { x += rhs.val(); if(x >= Mod) x -= Mod; return *this; }
	constexpr ModInt& operator-=(const ModInt& rhs) & { x -= rhs.val(); if(x >= Mod) x += Mod; return *this; }
	constexpr ModInt& operator*=(const ModInt& rhs) & { x = mulMod<Mod>(x, rhs.val()); return *this; }
	constexpr ModInt& operator/=(const ModInt& rhs) & { return *this *= rhs.inv(); }
	friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
	friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
	friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
	friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
	friend constexpr std::strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
	friend std::istream& operator>>(std::istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
	friend std::ostream& operator<<(std::ostream& os, const ModInt& a) { os << a.val(); return os; }
	constexpr ModInt pow(i64 b) const { ModInt res = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
private:
	U x;
};

using Z = ModInt<u32, 998244353>;

using poly = Poly<ModInt<u32, 998244353>>;

int main () {

}