#include <bits/stdc++.h>

using u64 = unsigned long long;

template<typename T>
std::vector<T> NTT(std::vector<T> a, std::vector<T> b) {
	static constexpr u64 P = T::mod();
	static constexpr  T  g = 3;
	static std::vector<T> rt { 0, 1 };

	int tot = a.size() + b.size() - 1;
	int k = std::__lg(tot), n = 1 << (k + 1);

	std::vector<int> rev(n);
	for (int i = 0; i < n; ++i) {
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
	}

	if ((int) rt.size() < n) {
		int k = std::countr_zero(rt.size());
		rt.resize(n);
		for (; (1 << k) < n; ++k) {
			auto e = g.pow((P - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); ++i) {
				rt[i << 1] = rt[i];
				rt[i << 1 | 1] = rt[i] * e;
			}
		}
	}

	auto dft = [&](std::vector<T>& f) {
		for (int i = 0; i < n; ++i) {
			if (i < rev[i]) {
				std::swap(f[i], f[rev[i]]);
			}
		}
		for (int i = 1; i < n; i <<= 1) {
			for (int j = 0; j < n; j += 2 * i) {
				for (int k = 0; k < i; ++k) {
					T fx = f[j + k], fy = f[i + j + k] * rt[i + k];
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
	T inv = T(n).inv();
	for (int i = 0; i < tot; ++i) {
		a[i] *= inv;
	}
	return a;
}

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using u128 = unsigned __int128;

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

int main () {
	int n, m;
	std::cin >> n >> m;
	n++, m++;

	std::vector<Z> A(n), B(m);
	for (int i = 0; i < n; ++i) {
		std::cin >> A[i];
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> B[i];
	}

	auto f = NTT(A, B);
	for (int i = 0; i < n + m - 1; ++i) {
		std::cout << f[i] << " \n"[i == n + m - 2];
	}
}
