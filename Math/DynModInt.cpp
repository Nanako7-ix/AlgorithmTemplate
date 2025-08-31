#include <bits/stdc++.h>

using u32  = unsigned;
using i64  = long long;
using u64  = unsigned long long;
using u128 = unsigned __int128;

template<std::unsigned_integral U>
constexpr U exgcd(U a, U b, U& x, U& y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	U d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

struct Barrett {
public:
	Barrett(u32 x) : m(x), im((u64)(-1) / x + 1) {}
	constexpr u32 Mod() const { return m; }
	constexpr u32 mul(u32 a, u32 b) const {
		u64 z = 1LL * a * b;
		u64 x = u64((u128(z) * im) >> 64);
		u32 v = u32(z - x * m);
		if (m <= v) v += m;
		return v;
	}
private:
	u32 m;
	u64 im;
};

template<u32 ID>
struct DynModInt {
public:
	constexpr DynModInt() : x(0) {}
	template<std::unsigned_integral T> constexpr DynModInt(T v) : x(v % Mod()) {}
	template<std::signed_integral T> constexpr DynModInt(T v) { int t = v % i64(Mod()); if (t < 0) t += Mod(); x = t; }
	constexpr static void setMod(u32 m) { bt = m; }
	constexpr static u32 Mod() { return bt.Mod(); }
	constexpr u32 val() const { return x; }
	constexpr DynModInt operator-() const { return x == 0 ? 0 : Mod() - x; }
	constexpr DynModInt inv() const { i64 x, y; assert(exgcd(this -> x, Mod(), x, y) == 1); return x; }
	constexpr DynModInt& operator+=(const DynModInt& rhs) & { x += rhs.val(); if (x >= Mod()) x -= Mod(); return *this; }
	constexpr DynModInt& operator-=(const DynModInt& rhs) & { x -= rhs.val(); if (x >= Mod()) x += Mod(); return *this; }
	constexpr DynModInt& operator*=(const DynModInt& rhs) & { x = bt.mul(x, rhs.val()); return *this; }
	constexpr DynModInt& operator/=(const DynModInt& rhs) & { return *this *= rhs.inv(); }
	friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt& rhs) { return lhs += rhs;}
	friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt& rhs) { return lhs -= rhs;}
	friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt& rhs) { return lhs *= rhs;}
	friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt& rhs) { return lhs /= rhs;}
	friend constexpr std::strong_ordering operator<=> (const DynModInt &lhs, const DynModInt &rhs) = default;
	friend std::istream& operator>>(std::istream& is, DynModInt& a) { i64 x; is >> x; a = DynModInt (x); return is; }
	friend std::ostream& operator<<(std::ostream& os, const DynModInt& a) { os << a.val(); return os; }
	constexpr DynModInt pow(i64 b) const { DynModInt res = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
private:
	u32 x;
	static Barrett bt;
};

template<u32 ID> Barrett DynModInt<ID>::bt = 998244353;
