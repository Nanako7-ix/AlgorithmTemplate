// validated by: https://judge.yosupo.jp/submission/318747
#include <random>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using u64 = unsigned long long;

struct SplitMix {
	static u64 shift(u64 x) {
		x += 0x9E37'79B9'7F4A'7C15ULL;
		x = (x ^ (x >> 30)) * 0xBF58'476D'1CE4'E5B9ULL;
		x = (x ^ (x >> 27)) * 0x94D0'49BB'1331'11EBULL;
		return x ^ (x >> 31);
	}
	u64 operator() (const u64& x) const {
		static const u64 rng = std::random_device()();
		return shift(x + rng);
	}
};

template<std::integral K, typename V>
using HashMap = __gnu_pbds::gp_hash_table<K, V, SplitMix>;
