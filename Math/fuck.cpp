#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

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
	constexpr ModInt& operator++() { *this += 1; return *this; }
	constexpr ModInt& operator--() { *this -= 1; return *this; }
	constexpr ModInt operator++(int) { auto tmp = *this; *this += 1; return tmp; }
	constexpr ModInt operator--(int) { auto tmp = *this; *this -= 1; return tmp; }
	friend constexpr std::strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
	friend std::istream& operator>>(std::istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
	friend std::ostream& operator<<(std::ostream& os, const ModInt& a) { os << a.val(); return os; }
	constexpr ModInt pow(i64 b) const { ModInt res = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
private:
	U x;
};

using Z = ModInt<u32, 1000000007>;

void Thephix() {
	int n, k;
	cin >> n >> k;
	
	vector<Z> fac(n + 1), inv(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = fac[i - 1] * i;
	}
	inv[n] = fac[n].inv();
	for (int i = n; i >= 1; --i) {
		inv[i - 1] = inv[i] * i;
	}

	vector<Z> pow(n + 1);
	pow[0] = 2;
	for (int i = 1; i <= n; ++i) {
		pow[i] = pow[i - 1] * pow[i - 1];
	}

	auto C = [&](int n, int m) -> Z {
		if (n < 0 || m < 0 || n < m) return 0;
		return fac[n] * inv[m] * inv[n - m];
	};

	Z ans = 0;
	for (int i = k; i <= n; ++i) {
		ans += ((i - k) % 2 == 0 ? 1 : -1) * C(i, k) * C(n, i) * pow[n - i] - 1;
	}
	cout << ans << '\n';
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
