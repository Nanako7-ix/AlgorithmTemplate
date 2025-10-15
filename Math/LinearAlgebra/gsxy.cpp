std::vector<std::vector<F>> A;
std::vector<V> B

for (int i = j; i < n; ++i) {
	for (int j = 0; j < n; ++j) {
		if (A[i][j] == F()) continue;
		if (i != j) {
			swap(A[i], A[j]);
			swap(B[i], B[j]);
		}
		break;
	}
	
	F c = A[j][j];
	for (int k = j; k < n; ++k) {
		A[j][k] /= c;
	} B[j] /= c;

	for (int i = 0; i < n; ++i) {
		if (i == j || A[i][j] == 0) continue;
		F c = A[i][j];
		for (int k = j; k < n; ++k) {
			A[i][k] -= A[j][k] * c;
		} B[i] -= B[j] * c;
	}
}
