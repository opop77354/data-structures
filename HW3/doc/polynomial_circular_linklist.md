# HW 2 多項式--環狀串列


## 1. 解題說明

這些函數實作了多項式的基本運算。通過使用帶有頭節點的循環列表來表示多項式，我們可以進行加、減、乘法等運算。使用 istream 和 ostream 運算多載子，使多項式的輸入輸出變得簡單。複製建構子和賦值運算子確保多項式對象在複製和賦值時的正確操作，而解構函數則負責釋放內存，避免內存洩漏。最後，Evaluate 函數可以快速計算多項式在代入值的結果。

## 2. 演算法設計與實作

term類別

```cpp
struct Term {
    float coef;
    int exp;
    Term* next;
};
```
polynimial類別

```cpp
class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& x);
    friend istream& operator>>(istream& is, Polynomial& x);
private:
    Term* first;
    void copy(const Polynomial& a);
    void clear();
public:
    Polynomial() : first(nullptr) {}
    Polynomial(const Polynomial& a);
    ~Polynomial();
    const Polynomial& operator=(const Polynomial& a);
    Polynomial operator+(const Polynomial& b) const;
    Polynomial operator-(const Polynomial& b) const;
    Polynomial operator*(const Polynomial& b) const;
    float Evaluate(float x) const;
    void newTerm(float coef, int exp);
};

```

istream& operator>>(istream& is, Polynomial& x):讀入輸入多項式並使用頭節點將其轉換為其循環列表表示。
```cpp
istream& operator>>(istream& is, Polynomial& x) {
    float coef;
    int exp;
    while (true) {
        is >> coef >> exp;
        if (coef == 0 && exp == 0) break;  // 終止條件
        if (coef != 0) x.newTerm(coef, exp);
    }
    return is;
}

```

ostream& operator<<(ostream& os, Polynomial& x):將 x 從其鍊錶表示轉換為其外部表示並輸出。

```cpp
ostream& operator<<(ostream& os, const Polynomial& x) {
    if (!x.first) {
        os << "0";
        return os;
    }

    Term* current = x.first;
    bool firstTerm = true;

    do {
        if (!firstTerm) {
            if (current->coef > 0) {
                os << " + ";
            }
            else {
                os << " - ";
            }
        }
        else if (current->coef < 0) {
            os << "-";
        }

        os << abs(current->coef);
        if (current->exp != 0) {
            os << "x^" << current->exp;
        }

        firstTerm = false;
        current = current->next;
    } while (current != x.first);

    return os;
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

初始化aPos、bPos = 0，

第一次迭代，terms[aPos].exp:terms[bPos].exp = 2 : 4，而 2 < 4，將B前項 6x^4 添加到 c，並將bPos往前一位，bPos = 1;

第二次迭代，terms[aPos].exp:terms[bPos].exp = 2 : 3，而 2 < 3，將B前項 2x^3 添加到 c，並將bPos往前一位，bPos = 2;

第三次迭代，terms[aPos].exp:terms[bPos].exp = 2 : 1，而 2 < 1，將A前項 3x^2 添加到 c，並將aPos往前一位，aPos = 1;

第四次迭代，terms[aPos].exp:terms[bPos].exp = 1 : 1，而 1 = 1，將兩項係數相加 2 + 1 = 3，並將新項 3x^1 添加到 c，並將aPos和bPos都往前一位，aPos = 2, bPos = 3;

第五次迭代，terms[aPos].exp:terms[bPos].exp = 0 : 0，而 0 = 0，將兩項係數相加 4 + 8 = 12，並將 12x^0 添加到 c，並將aPos和bPos都往前一位，aPos = 3, bPos = 4，

回傳結果6x^4 + 2x^3 + 3x^2 + 3x^1 + 12。

乘法函式:

當 i = 0，而 j = 0，newcoef = 3 * 6 = 18，newexp = 2 + 4 = 6，產生新項 18x^6 加到 c

當 i = 0，而 j = 1，newcoef = 3 * 2 = 6，newexp = 2 + 3 = 5，產生新項 6x^5 加到 c

當 i = 0，而 j = 2，newcoef = 3 * 1 = 3，newexp = 2 + 1 = 3，產生新項 3x^3 加到 c

當 i = 0，而 j = 3，newcoef = 3 * 8 = 24，newexp = 2 + 0 = 2，產生新項 24x^2 加到 c

當 i = 1，而 j = 0，newcoef = 2 * 6 = 12，newexp = 1 + 4 = 5，產生新項 12x^5 加到 c，合併到 6x^5，為 18x^5

當 i = 1，而 j = 1，newcoef = 2 * 2 = 4，newexp = 1 + 3 = 4，產生新項 4x^4 加到 c

當 i = 1，而 j = 2，newcoef = 2 * 1 = 2，newexp = 1 + 1 = 2，產生新項 2x^2 加到 c，合併到 24x^5，為 26x^5

當 i = 1，而 j = 3，newcoef = 2 * 8 = 16，newexp = 1 + 0 = 1，產生新項 16x^1 加到 c

當 i = 2，而 j = 0，newcoef = 4 * 6 = 24，newexp = 0 + 4 = 4，產生新項 24x^4 加到 c，合併到 4x^4，為 28x^4

當 i = 2，而 j = 1，newcoef = 4 * 2 = 8，newexp = 0 + 3 = 3，產生新項 8x^3 加到 c，合併到 3x^3，為 11x^3

當 i = 2，而 j = 2，newcoef = 4 * 1 = 4，newexp = 0 + 1 = 1，產生新項 4x^1 加到 c，合併到 16x^1，為 20x^1

當 i = 2，而 j = 3，newcoef = 4 * 8 = 32，newexp = 0 + 0 = 0，產生新項 32 加到 c

回傳結果18x^6 + 18x^5 + 11x^3 + 26x^2 + 28x^4 + 20x^1 + 32

代數運算函式:

初始化result = 0

當 i = 0，terms[0].coef = 3，terms[0].exp = 2，3 * pow(2, 2) = 3 * 4 = 12，result 0 + 12 = 12

當 i = 1，terms[1].coef = 2，terms[1].exp = 1，2 * pow(2, 1) = 2 * 2 = 4，result 12 + 4 = 16

當 i = 2，terms[2].coef = 4，terms[2].exp = 0，4 * pow(2, 0) = 4 * 1 = 4，result 16 + 4 = 20

回傳結果20

