# HW 1 阿克曼函數

## 1. 解題說明

假設兩個未知數m、n。
此函數定義:
A(m,n) = 當m = 0，n + 1;
         當m > 0 且 n = 0，A(m – 1, 1);
         當m > 0 且 n > 0，A(m – 1, A(m, n - 1));

實作參見檔案 `ack.cpp`，其遞迴函式：

```cpp
int ack(int m, int n)
{
	if (m == 0)
	{
		return n + 1;
	}
	else if (n == 0)
	{
		return ack(m - 1, 1);
	}
	else
	{
		return ack(m - 1, ack(m, n - 1));
	}
}
```

## 2. 演算法設計與實作

```cpp
int main()
{
	int m;
	int n;
	cin >> m;
	cin >> n;
	ack(m, n);
	cout << ack(m, n) << endl;
}
```

## 2. 效能分析

- $f(n) = O(n)$
- $S(P) = 1 \times n$, 1 個變數、n 次遞迴。
- $T(P) = C \times n$, 每層迴圈所需 C 時間、n 次遞迴。

## 3. 測試與過程

### Input

```plain
3
7
11

```

### Output

```plain
6
28
66

```

### 驗證

此函式遞迴終止條件為當 $n$ 為 $0$ 或 $1$，若欲求得$3!$，則呼叫 $sigma(3)$，進入函式後，首先第一層 $n = 3 > 1$ 所以回傳 $n + sigma(n - 1)$，即 $3 + sigma(2)$，接著第二層計算 $sigma(2)$，$n = 2 > 1$，所以回傳 $2 + sigma(1)$，接下來到第三層時，$n = 1 \le 1$，符合終止條件 $(n \le 1)$，因此回傳 $n$，即 $1$。

$$sigma(3) = 3 + sigma(2) = 3+2 + sigma(1) = 3+2+1 = 6$$
