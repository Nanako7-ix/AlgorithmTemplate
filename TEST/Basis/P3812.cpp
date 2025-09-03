#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<int N>
struct Basis : std::array<u64, N> {
	using std::array<u64, N>::at;
	
	void insert(u64 x) {
		for (int i = N - 1; i >= 0; --i) {
			if (x >> i & 1) {
				if (at(i) == 0) {
					at(i) = x;
					break;
				}
				x ^= at(i);
			}
		}
	}

	bool exist(u64 x) {
		for (int i = N - 1; i >= 0; --i) {
			if (x >> i & 1) {
				if (at(i) == 0) {
					return false;
				}
			}
		}
		return true;
	}
};

void Thephix() {
	int n;
	cin >> n;
	Basis<50> basis {};
	for (int i = 1; i <= n; ++i) {
		i64 x; cin >> x;
		basis.insert(x);
	}
	u64 ans = 0;
	for (int i = 49; i >= 0; --i) {
		ans = max(ans, ans ^ basis[i]);
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
