#include <bits/stdc++.h>
using i64 = long long;

i64 floor_div(i64 u, i64 d) {
	assert(d != 0);
	i64 k = u / d, r = u % d;
	if (r >= 0) return k;
	if (d > 0) return k - 1;
	if (d < 0) return k + 1;
	__builtin_unreachable();
}

i64 floor_mod(i64 u, i64 d) {
	assert(d != 0);
	i64 r = u % d;
	if (r >= 0) return r;
	if (d > 0) return r + d;
	if (d < 0) return r - d;
	__builtin_unreachable();
}

i64 ceil_div(i64 u, i64 d) {
	assert(d != 0);
	i64 k = u / d, r = u % d;
	if (r <= 0) return k;
	if (d > 0) return k + 1;
	if (d < 0) return k - 1;
	__builtin_unreachable();
}

i64 ceil_mod(i64 u, i64 d) {
	assert(d != 0);
	i64 r = u % d;
	if (r <= 0) return r;
	if (d > 0) return r - d;
	if (d < 0) return r + d;
	__builtin_unreachable();
}
