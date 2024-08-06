# HW 2 多項式--陣列

## 1. 解題說明

假設兩個多項式

A:3x^2 + 2x + 4

B:6x^4 + 2x^3 + x + 8

將兩式相加

A + B = 6x^4 + 2x^3 + 3x^2 + 3x + 12

將兩式相乘

A * B = 18x^6 + 18x^5 + 11x^3 + 26x^2 + 28x^4 + 20x^1 + 32

把多項式拆分成個體看，再將每以個體拆分成零件，零件包含項次、係數、指數。

## 2. 演算法設計與實作

term類別

```cpp
class Term {
public:
    float coef;
    int exp;
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};
```
polynimial類別

```cpp
class Polynomial {
public:
    Polynomial(int d = 0); // 建構函數
    ~Polynomial();  // 解構函數

    Polynomial(const Polynomial& other); // 複製建構函數
    Polynomial& operator=(const Polynomial& other);

    void AddTerm(float coef, int exp);
    Polynomial Add(const Polynomial& b) const;
    Polynomial Mult(const Polynomial& b) const;
    float Eval(float x) const;
    void Output() const;

private:
    Term* terms;
    int size; // 當前多項式項數
    int capacity; // 當前陣列容量

    void Resize(int new_capacity);
    void AddOrUpdateTerm(float coef, int exp); // 合併或更新項
};

```

多項式運算-ADD函數
```cpp
Polynomial Polynomial::Add(const Polynomial& b) const {
    Polynomial c(size + b.size);

    int aPos = 0;
    int bPos = 0;

    while (aPos < size && bPos < b.size) {
        if (terms[aPos].exp == b.terms[bPos].exp) {
            float t = terms[aPos].coef + b.terms[bPos].coef;
            if (t != 0) c.AddTerm(t, terms[aPos].exp);
            ++aPos;
            ++bPos;
        }
        else if (terms[aPos].exp < b.terms[bPos].exp) {
            c.AddTerm(b.terms[bPos].coef, b.terms[bPos].exp);
            ++bPos;
        }
        else {
            c.AddTerm(terms[aPos].coef, terms[aPos].exp);
            ++aPos;
        }
    }

    while (aPos < size) {
        c.AddTerm(terms[aPos].coef, terms[aPos].exp);
        ++aPos;
    }

    while (bPos < b.size) {
        c.AddTerm(b.terms[bPos].coef, b.terms[bPos].exp);
        ++bPos;
    }

    return c;
}

```

多項式運算-mult

```cpp
Polynomial Polynomial::Mult(const Polynomial& b) const {
    Polynomial c(size * b.size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < b.size; ++j) {
            float newCoef = terms[i].coef * b.terms[j].coef;
            int newExp = terms[i].exp + b.terms[j].exp;
            c.AddOrUpdateTerm(newCoef, newExp);
        }
    }

    return c;
}

```
多項式代數運算

```cpp
float Polynomial::Eval(float x) const {
    float result = 0;
    for (int i = 0; i < size; ++i) {
        result += terms[i].coef * pow(x, terms[i].exp);
    }
    return result;
}

```

主程式

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
建構函數:
- 時間複雜度O(1)，初始化並分配空間

加法函式:
- 時間複雜度O(n + m)，其中 n 和 m 分別是兩個多項式的項數
- 空間複雜度O(n + m)，分配一個空間來存儲結果

乘法函式:
- 時間複雜度O(n * m)，其中 n 和 m 分別是兩個多項式的項數
- 空間複雜度O(n * m)，多項式乘積

代數函式:
- 時間複雜度O(n)，n是多項式項數
- 空間複雜度O(1)，需要額外空間給常數
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
以範例來做推演:

A:3x^2 + 2x + 4

B:6x^4 + 2x^3 + x + 8

建構函式:

初始化size = 0，capacity = 3，terms去指向一個包含3個term的陣列。

相加函式:

初始化aPos、bPos = 0，第一次迭代
