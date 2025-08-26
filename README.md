# AlgorithmTemplate

XCPC 算法模板

如果有错误，请告诉我

## String

### 字符串哈希

核心公式，也就是第 $i$ (从 $0$ 开始) 个字符的系数是 $x^{n - i + 1}$

$$
hash(s) = \sum\limits s_i \cdot x^{n - i + 1}
$$

这条公式在部分情况下可以 $O(1)$ 内计算出一个和 $s$ 类似的字符串 $t$ 的哈希值。

### Manacher

一个字符串成为回文串当且仅当它正着读和反着读相等。令 $\overline{s}$ 为 $s$ 的 reverse，那么 $s$ 是回文串当且仅当 $s = \overline{s}$。

Manacher 可以求出对于 $2n - 1$ 个回文中心的最长回文半径。我们把字符串构造成 $s'$，满足：

$$
s'_i =
\begin{cases}
\# & i \bmod 2 \equiv 0\\
s_\frac{i - 1}{2} & i \bmod 2 \equiv 1
\end{cases}
$$

所以 Manacher 的一个难点在于 $s'$ 的下标和原字符串的位置的转换：

原字符串的第 $$

### KMP

前缀函数，`KMP` 中的核心，定义 $f(s)$ 为 $s$ 的最长真前后缀的长度。