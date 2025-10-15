std::array<u64, N> basis {};

bool insert(u64 x) {
	for (int i = N - 1; i >= 0; --i) {
		if (x >> i & 1) {
			if (basis[i] == 0) {
				basis[i] = x;
				return true;
			}
			x ^= basis[i];
		}
	}
	return false;
}

bool contains(u64 x) {
	for (int i = N - 1; i >= 0; --i) {
		if (x >> i & 1) {
			if (basis[i] == 0) {
				basis[i] = x;
				return false;
			}
			x ^= basis[i];
		}
	}
	return true;
}
