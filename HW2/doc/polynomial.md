# HW 2 多項式--陣列

## 1. 解題說明

假設兩個多項式

A:3x^2 + 2x + 4

B:6x^4 + 2x^3 + x + 8

將兩式相加

A + B = 6x^4 + 2x^3 + 3x^2 + 3x + 12

將兩式相乘

A * B = 18x^6 + 18x^5 + 11x^3 + 26x^2 + 28x^4 + 20x^1 + 32

## 2. 演算法設計與實作

```cpp
int main() {
    int numTerms1, numTerms2;

    cout << "terms for polynomial 1: ";
    cin >> numTerms1;
    Polynomial p1(numTerms1);

    cout << "coef for polynomial 1: ";
    float* coefs1 = new float[numTerms1];
    for (int i = 0; i < numTerms1; ++i) {
        cin >> coefs1[i];
    }

    cout << "exp for polynomial 1: ";
    int* exps1 = new int[numTerms1];
    for (int i = 0; i < numTerms1; ++i) {
        cin >> exps1[i];
        p1.AddTerm(coefs1[i], exps1[i]);
    }

    cout << "terms for polynomial 2: ";
    cin >> numTerms2;
    Polynomial p2(numTerms2);

    cout << "coef for polynomial 2: ";
    float* coefs2 = new float[numTerms2];
    for (int i = 0; i < numTerms2; ++i) {
        cin >> coefs2[i];
    }

    cout << "exp for polynomial 2: ";
    int* exps2 = new int[numTerms2];
    for (int i = 0; i < numTerms2; ++i) {
        cin >> exps2[i];
        p2.AddTerm(coefs2[i], exps2[i]);
    }

    Polynomial p3 = p1.Add(p2);
    Polynomial p4 = p1.Mult(p2);

    cout << "Polynomial 1: ";
    p1.Output();
    cout << "Polynomial 2: ";
    p2.Output();
    cout << "p1 + p2: ";
    p3.Output();
    cout << "p1 * p2: ";
    p4.Output();

    float x;
    cout << " value for x to evaluate polynomial 1: ";
    cin >> x;
    cout << "p1 evaluated at x = " << x << ": " << p1.Eval(x) << endl;

    delete[] coefs1;
    delete[] exps1;
    delete[] coefs2;
    delete[] exps2;

    return 0;
}
```

## 3. 效能分析
時間複雜度:
- 當 m = 0 時，函數的時間複雜度是O(1)，因為只有一個基本運算。
- 當 n = 0 且 m > 0 時，函數的時間複雜度是O(n)，因為它遞歸呼叫自身n次。
- 當 m > 0 且 n > 0 時，函數的時間複雜度非常高，可以說是超過指數等級的成長。

## 4. 測試與過程

### Input

```plain
Enter number of terms for polynomial 1: 3
Enter the coefficients for polynomial 1: 3 2 4
Enter the exponents for polynomial 1: 2 1 0
Enter number of terms for polynomial 2: 4
Enter the coefficients for polynomial 2: 6 2 1 8
Enter the exponents for polynomial 2: 4 3 1 0
Enter a value for x to evaluate polynomial 1: 2

```

### Output

```plain
Polynomial 1: 3x^2+2x^1+4
Polynomial 2: 6x^4+2x^3+1x^1+8
p1 + p2: 6x^4+2x^3+3x^2+3x^1+12
p1 * p2: 18x^6+18x^5+11x^3+26x^2+28x^4+20x^1+32
p1 evaluated at x = 2: 20

```

### 驗證

以範例來驗證:

$$A(3, 3) = m > 0, n > 0; ==>A(2, A(3, 2))$$

將A(3, 2)提出並計算

$$A(3, 2) = m > 0, n > 0; ==>A(2, A(3, 1))$$

重複步驟直到A(3, 0)

$$A(3, 1) = m > 0, n > 0; ==>A(2, A(3, 0))$$

此時函式展開為

$$A(2, 2, 2, A(3, 0))$$

將A(3, 0)提出並計算

$$A(3, 0) = m > 0, n = 0; ==>A(2, 1)$$

依此類推

$$A(2, 2, 2, A(2, 1)) =$$

$$A(2, 2, 2, 1, A(2, 0)) =$$

$$A(2, 2, 2, 1, A(1, 1)) =$$

$$A(2, 2, 2, 1, 0, A(1, 0)) =$$

$$A(2, 2, 2, 1, 0, A(0, 1)) =$$

$$A(2, 2, 2, 1, A(0, 2)) =$$

$$A(2, 2, 2, A(1, 3)) =$$

$$A(2, 2, 2, 0, A(1, 2)) =$$

$$A(2, 2, 2, 0, 0, A(1, 1)) =$$

$$A(2, 2, 2, 0, 0, 0, A(1, 0)) =$$

$$A(2, 2, 2, 0, 0, 0, A(0, 1)) =$$

$$A(2, 2, 2, 0, 0, A(0, 2)) =$$

$$A(2, 2, 2, 0, A(0, 3)) =$$

$$A(2, 2, 2, A(0, 4)) =$$

$$A(2, 2, A(2, 5)) =$$

$$A(2, 2, 1, A(2, 4)) =$$

$$A(2, 2, 1, 1, A(2, 3)) =$$

$$A(2, 2, 1, 1, 1, A(2, 2)) =$$

$$A(2, 2, 1, 1, 1, 1, A(2, 1)) =$$

$$A(2, 2, 1, 1, 1, 1, 1, A(2, 0)) =$$

$$A(2, 2, 1, 1, 1, 1, 1, A(1, 1)) =$$

$$A(2, 2, 1, 1, 1, 1, 1, 0, A(1, 0)) =$$

$$A(2, 2, 1, 1, 1, 1, 1, 0, A(0, 1)) =$$

$$A(2, 2, 1, 1, 1, 1, 1, A(0, 2)) =$$

$$A(2, 2, 1, 1, 1, 1, A(1, 3)) =$$

$$A(2, 2, 1, 1, 1, 1, 0, A(1, 2)) =$$

$$A(2, 2, 1, 1, 1, 1, 0, 0, A(1, 1)) =$$

$$A(2, 2, 1, 1, 1, 1, 0, 0, 0, A(1, 0)) =$$

$$A(2, 2, 1, 1, 1, 1, 0, 0, 0, A(0, 1)) =$$

$$A(2, 2, 1, 1, 1, 1, 0, 0, A(0, 2)) =$$

$$A(2, 2, 1, 1, 1, 1, 0, A(0, 3)) =$$

$$A(2, 2, 1, 1, 1, 1, A(0, 4)) =$$

$$A(2, 2, 1, 1, 1, A(1, 5)) =$$

$$A(2, 2, 1, 1, 1, 0, A(1, 4)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, A(1, 3)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, 0, A(1, 2)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, 0, 0, A(1, 1)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, 0, 0, 0, A(1, 0)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, 0, 0, A(0, 2)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, 0, A(0, 3)) =$$

$$A(2, 2, 1, 1, 1, 0, 0, A(0, 4)) =$$

$$A(2, 2, 1, 1, 1, 0, A(0, 5)) =$$

$$A(2, 2, 1, 1, 1, A(0, 6)) =$$

$$A(2, 2, 1, 1, A(1, 7)) =$$

$$A(2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, A(1, 0)) =$$

$$A(2, 2, 1, A(1, 9)) =$$

$$A(2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, A(1, 0)) =$$

$$A(2, 2, A(1, 11)) =$$

$$A(2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, A(1, 0)) =$$

$$A(2, A(2, 13)) =$$

$$A(2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, A(1, 1)) =$$

$$A(2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, A(1, 0)) =$$

$$A(2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, A(1, 3)) =$$

$$A(2, 31) =$$

$$A(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, A(2, 0)) =$$

$$A(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, A(1, 0)) =$$

$$ = 61$$
