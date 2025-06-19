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

**回文**中判定相等的谓词 $f$ 需要满足的性质是：

$$
\begin{cases}
f(x, x^\prime)\\
f(y, y^\prime)\\
f(x, y)\\
\end{cases}
\Rightarrow
f(y^\prime, x^\prime)
$$

以我的能力，可以推出一个充分条件是：$f$ 是一个等价谓词。

### KMP

前缀函数，`KMP` 中的核心，定义 $f(s)$ 为 $s$ 的最长真前后缀的长度。