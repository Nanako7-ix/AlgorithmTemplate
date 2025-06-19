# AlgorithmTemplate

XCPC 算法模板

如果有错误，请告诉我

## String

### 字符串哈希

核心公式，也就是第 $i$ （0-base）个字符的系数是 $x^{n - i + 1}$

$$
hash(s) = \sum\limits s_i \cdot x^{n - i + 1}
$$

### Manacher

`check` 需要满足的性质是：

$$
\begin{cases}
f(x, x^\prime)\\
f(y, y^\prime)\\
f(x, y)\\
\end{cases}
\Rightarrow
f(y^\prime, x^\prime)
$$

这似乎只知道 $f$ 是等价关系，这是一个非充要条件。