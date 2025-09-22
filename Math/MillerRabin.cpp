#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

template<typename T>
bool is_prime(const T& x) {
  if (x == 2 || x == 3 || x == 5 || x == 7) return true;
  if (x < 2 || x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
  if (x < 121) return x > 1;
  const T d = (x - 1) >> __builtin_ctzll(x - 1);
  auto isok = [&](T a) -> bool {
    T y = 1, t = d;
    for (T i = a, j = d; j; j >>= 1) {
      if (j & 1) y = (i128) y * i % x;
      i = (i128) i * i % x;
    }
    while (y != 1 && y != x - 1 && t != x - 1) {
      y = (i128) y * y % x;
      t <<= 1;
    }
    return y == x - 1 || t % 2 == 1;
  };

  if (x < (1LL << 32)) for (T a : { 2, 7, 61 }) {
    if (!isok(a)) return false;
  } else for (T a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
    if (!isok(a)) return false;
  }
  return true;
}
