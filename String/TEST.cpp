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
	friend constexpr std::strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
	friend std::istream& operator>>(std::istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
	friend std::ostream& operator<<(std::ostream& os, const ModInt& a) { os << a.val(); return os; }
	constexpr ModInt pow(i64 b) const { ModInt res = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
private:
	U x;
};

using Z = ModInt<u32, 998244353>;

constexpr array<Z, 2> x {  Z(131) , Z( 131 ).inv() };
constexpr array<Z, 2> y { Z(13331), Z(13331).inv() };

array<Z, 3000> px = []() {
	px[0] = 1;
	for (int i = 1; i < 3000; ++i) {
		px[i] = px[i - 1] * x[0];
	}
	return px;
} ();

array<Z, 3000> py = []() {
	py[0] = 1;
	for (int i = 1; i < 3000; ++i) {
		py[i] = py[i - 1] * y[0];
	}
	return py;
} ();

void Thephix() {
	int n, m;
	cin >> n >> m;

	int N = 2 * n + 1;
	int M = 2 * m + 1;
	vector<vector<int>> a(N + 1, vector<int> (M + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i << 1][j << 1];
		}
	}

	vector<vector<Z>> f(N + 1, vector<Z> (M + 1));
	vector<vector<Z>> g(N + 1, vector<Z> (M + 1));
	vector<vector<Z>> h(N + 1, vector<Z> (M + 1));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			f[i][j] = (a[i][j] + 1) + f[i][j - 1] * y[0] + f[i - 1][j] * x[0] - f[i - 1][j - 1] * x[0] * y[0];
			g[i][j] = (a[i][j] + 1) + g[i][j - 1] * y[1] + g[i - 1][j] * x[0] - g[i - 1][j - 1] * x[0] * y[1];
			h[i][j] = (a[i][j] + 1) + h[i][j - 1] * y[0] + h[i - 1][j] * x[1] - h[i - 1][j - 1] * x[1] * y[0];
		}
	}

	auto check = [&](int xl, int xr, int yl, int yr) {
		Z A = f[xr][yr] - f[xl - 1][yr] * px[xr - xl + 1] - f[xr][yl - 1] * py[yr - yl + 1] + f[xl - 1][yl - 1] * px[xr - xl + 1] * py[yr - yl + 1];
		Z B = g[xr][yr] * py[yr - yl] - g[xl - 1][yr] * px[xr - xl + 1] * py[yr - yl] - g[xr][yl - 1] * y[1] + g[xl - 1][yl - 1] * px[xr - xl + 1] * y[1];
		Z C = h[xr][yr] * px[xr - xl] - h[xl - 1][yr] * x[1] - h[xr][yl - 1] * py[yr - yl + 1] * px[xr - xl] + h[xl - 1][yl - 1] * x[1] * py[yr - yl + 1];
		return A == B && A == C;
	};

	i64 ans = 0;
	for (int i = 1; i <= N; ++i) {
		// 其实意思是 i = j (mod 2) 的情况下有贡献
		for (int j = (i % 2 == 1 ? 3 : 2); j <= M; j += 2) {
			int l = 1, r = min({ i, j, N - i + 1, M - j + 1 }), res = -1;
			while (l <= r) {
				int x = (l + r) >> 1;
				if (check(i - x + 1, i + x - 1, j - x + 1, j + x - 1)) {
					res = x, l = x + 1;
				} else r = x - 1;
			}
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
