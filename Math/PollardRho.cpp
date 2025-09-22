#include <bits/stdc++.h>
#include "MillerRabin.cpp"

using i64 = long long;
using i128 = __int128;

std::mt19937_64 rng_64((std::random_device())());
auto rng(i64 L, i64 R) { return rng_64() % (R - L + 1) + L; }

template<typename T>
T pollard_rho(T n) {
	if (n <= 1) return n;
	const T c = rng(1, n - 1);
	auto f = [&](T x) { return ((i128) x * x % n + c) % n; };
	T x = 1, y = 2, z = 1, q = 1, g = 1;
	const T m = 1LL << (__lg(n) / 5);
	for (T r = 1; g == 1; r <<= 1) {
		x = y;
		for (T i = 0; i < r; ++i) y = f(y);
		for (T k = 0; k < r && g == 1; k += m) {
			z = y;
			for (T i = 0; i < min(m, r - k); ++i) {
				y = f(y);
				q = (i128) q * abs(x - y) % n;
			}
			g = gcd(q, n);
		}
	}
	if (g == n) do {
		z = f(z);
		g = gcd(abs(x - z), n);
	} while (g == 1);
	return g;
}

template<typename T>
T find_prime_factor(T n) {
	if (is_prime(n)) return n;
	for (int i = 0; i < 100; ++i) {
		T p = pollard_rho(n);
		if (is_prime(p)) return p;
		n = p;
	}
	return -1;
}

template<typename T>
auto factor(T n) {
	std::vector<std::pair<T, int>> res;
	for (int p = 2; p * p <= n && p < 100; ++p) {
		if (n % p) continue;
		int e = 0;
		do { n /= p, e++; } while (n % p == 0);
		res.emplace_back(p, e);
	}
	while (n > 1) {
		T p = find_prime_factor(n);
		int e = 0;
		do { n /= p, e++; } while (n % p == 0);
		res.emplace_back(p, e);
	}
	return res;
}
