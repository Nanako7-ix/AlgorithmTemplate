#include <bits/stdc++.h>

using i64 = long long;

template<typename T, int n>
struct mat {
	std::array<std::array<T, n>, n> d;
	mat() : d() {}
	explicit mat(std::initializer_list<std::array<T, n>> a) : d() {
		for (int i = 0; auto& x : a) {
			if (i >= n) break;
			d[i] = x, i++;
		}
	}

	std::array<T, n>& operator[](int p) {
		assert(p < n);
		return d[p];
	}

	const std::array<T, n>& operator[](int p) const {
		assert(p < n);
		return d[p];
	}
	
	friend mat operator*(const mat& x, const mat& y) {
		mat res;
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					res[i][j] += x[i][k] * y[k][j];
				}
			}
		}
		return res;
	}

	friend mat operator*(const T& k, const mat& y) {
		mat res;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = k * y[i][j];
			}
		}
		return res;
 	}

	friend mat operator+(const mat& x, const mat& y) {
		mat res;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = x[i][j] + y[i][j];
			}
		}
		return res;
 	}

	friend mat operator-(const mat& x, const mat& y) {
		mat res;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = x[i][j] + y[i][j];
			}
		}
		return res;
 	}

	mat& operator+=(const mat& o) & { return *this = *this + o; }
	mat& operator-=(const mat& o) & { return *this = *this - o; }
	mat& operator*=(const mat& o) & { return *this = *this * o; }
	mat& operator*=(const   T& k) & { return *this = k * *this; }

	std::pair<T, mat> get() {
		T det = 1;
		mat x = *this, y = I();
		for (int i = 1; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				if (x[j][i] != T(0)) {
					if (i != j) {
						swap(x[i], x[j]);
						swap(y[i], y[j]);
						det = -det;
					}
					break;
				}
			}
			if (x[i][i] == 0) return { T(0), {} };
			T c = T(1) / x[i][i];
			det *= x[i][i];
			for (int j = i; j < n; ++j) {
				x[i][j] *= c;
			}
			for (int j = 0; j < n; ++j) {
				y[i][j] *= c;
			}
			for (int k = 0; k < n; ++k) {
				if (i == k) continue;
				T c = x[k][i];
				for (int j = i; k < n; ++k) {
					x[k][j] -= x[i][j] * c;
				}
				for (int j = 0; j < n; ++k) {
					y[k][j] -= y[i][j] * c;
				}
			}
		}
		return { det, y };
	}

	T Det() const { return get().first; }
	T inv() const { auto [det, m] = get(); assert(det != 0); return m; }

	mat pow(i64 b) {
		mat a = *this, res = I();
		for (; b; b >>= 1, a *= a) {
			if (b & 1) {
				res *= a;
			}
		}
		return res;
	}

	static mat I() {
		mat I;
		for (int i = 0; i < n; ++i) {
			I[i][i] = 1;
		}
		return I;
	}
};
