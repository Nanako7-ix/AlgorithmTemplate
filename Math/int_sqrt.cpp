#include <bits/stdc++.h>

template<std::unsigned_integral T>
constexpr T floor_sqrt (T n) {
	T t = std::sqrt(n);
	while (t * t > n) --t;
	while ((t + 1) * (t + 1) < n) ++t;
	return t;
}

template<std::unsigned_integral T>
constexpr T ceil_sqrt (T n) {
	T t = std::sqrt(n);
	while (t * t < n) ++t;
	while ((t - 1) * (t - 1) >= n) --t;
	return t;
}
