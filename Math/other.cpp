#include <bits/stdc++.h>

template<std::unsigned_integral T>
T floor_sqrt (T n) {
	T t = sqrt(n);
	while (t * t > n) --t;
	while ((t + 1) * (t + 1) < n) ++t;
	return t;
}

template<std::unsigned_integral T>
T ceil_sqrt (T n) {
	T t = sqrt(n);
	while (t * t < n) ++t;
	while ((t - 1) * (t - 1) >= n) --t;
	return t;
}

template<std::signed_integral T>
T floor_div(T a, T b) {
	return a / b;
}

template<std::signed_integral T>
T ceil_div(T a, T b) {
	return (a - 1) / b + 1;
}
