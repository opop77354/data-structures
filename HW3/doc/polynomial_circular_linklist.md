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
Polynomial::Polynomial(const Polynomial& a):將多項式 *this 初始化為多項式 a。

```cpp
void Polynomial::copy(const Polynomial& a) {
    if (!a.first) {
        first = nullptr;
        return;
    }

    Term* current = a.first;
    do {
        newTerm(current->coef, current->exp);
        current = current->next;
    } while (current != a.first);
}

Polynomial::Polynomial(const Polynomial& a) : first(nullptr) {
    copy(a);
}
```

const Polynomial& Polynomial::operator=(const Polynomial& a):將多項式 a 賦值給 *this。

```cpp
const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this == &a) return *this;

    clear();
    copy(a);
    return *this;
}
```

Polynomial::~Polynomial():將多項式 *this 的所有節點傳回可用空間清單。

```cpp
Polynomial::~Polynomial() {
    clear();
}

void Polynomial::clear() {
    if (!first) return;

    Term* current = first;
    Term* next = nullptr;
    do {
        next = current->next;
        delete current;
        current = next;
    } while (current != first);

    first = nullptr;
}

```


Polynomial Polynomial::operator+(const Polynomial& b) const:建立並傳回多項式*this + b。
```cpp
Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Term* current = first;
    do {
        result.newTerm(current->coef, current->exp);
        current = current->next;
    } while (current != first);

    current = b.first;
    do {
        result.newTerm(current->coef, current->exp);
        current = current->next;
    } while (current != b.first);

    return result;
}

```


Polynomial Polynomial::operator-(const Polynomial& b) const:建立並傳回多項式*this - b。
```cpp
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial negB;
    Term* current = b.first;
    do {
        negB.newTerm(-current->coef, current->exp);
        current = current->next;
    } while (current != b.first);

    return *this + negB;
}

```


Polynomial Polynomial::operator*(const Polynomial& b) const:建立並傳回多項式*this * b。
```cpp
Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;
    if (!first || !b.first) return result;  // Handle empty polynomials

    Term* a = first;
    do {
        Term* bPtr = b.first;
        do {
            result.newTerm(a->coef * bPtr->coef, a->exp + bPtr->exp);
            bPtr = bPtr->next;
        } while (bPtr != b.first);
        a = a->next;
    } while (a != first);

    return result;
}

```


float Polynomial::Evaluate(float x) const:計算 x 處的多項式 *this 並傳回結果。
```cpp

float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    Term* current = first;
    do {
        result += current->coef * pow(x, current->exp);
        current = current->next;
    } while (current != first);
    return result;
}

```


主程式
```cpp
int main() {
    Polynomial p1, p2;
    cout << "polynomial_1 :" << endl;
    cin >> p1;
    cout << "polynomial_2 :" << endl;
    cin >> p2;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;

    float x;
    cout << "value_x: ";
    cin >> x;

    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;
    cout << "p2(" << x << ") = " << p2.Evaluate(x) << endl;
    cout << "Sum(" << x << ") = " << sum.Evaluate(x) << endl;
    cout << "Difference(" << x << ") = " << diff.Evaluate(x) << endl;
    cout << "Product(" << x << ") = " << prod.Evaluate(x) << endl;

    return 0;
}

```
## 3. 效能分析
new term函數:
- 時間複雜度O(n)，：在最壞情況下，當多項式的項數為n時，可能需要遍歷整個環狀串列來找到正確的插入位置或更新現有節點。
- 空間複雜度O(1)，每次插入新項目時，會分配一個新的Term節點

加法函式:
- 時間複雜度O(n + m)，需要將兩個多項式的每一項進行相加。兩個多項式的每個項目都需要被處理一次。其中 n 和 m 分別是兩個多項式的項數
- 空間複雜度O(n + m)，每次新建立一個項目時，會分配新的節點空間

減法函式:
- 時間複雜度O(n + m)，減法運算是由加法運算改寫。先複製並取負數，再與另一個多項式相加。
- 空間複雜度O(n + m)，每次新建立一個項目時，會分配新的節點空間

乘法函式:
- 時間複雜度O(n * m)，每個多項式中的每一項都需要與另一個多項式中的每一項進行相乘，然後合併結果。其中 n 和 m 分別是兩個多項式的項數
- 空間複雜度O(n * m)，多項式的項數最多可能是 m * n

代數函式:
- 時間複雜度O(n)，需要遍歷多項式的每一項，對每一項進行計算。n是多項式項數
- 空間複雜度O(1)，不會分配額外的空間


## 4. 測試與過程

### Input

```plain
polynomial_1:
3 2
2 1
1 0
0 0
polynomial_2:
2 1
1 1
0 0

Enter value for x: 2

```

### Output

```plain
Polynomial 1: 3x^2 + 2x^1 + 1
Polynomial 2: 3x^1
Sum: 3x^2 + 5x^1 + 1
Difference: 3x^2 - 1x^1 + 1
Product: 9x^3 + 6x^2 + 3x^1

p1(2) = 17
p2(2) = 6
Sum(2) = 23
Difference(2) = 11
Product(2) = 102
```

### 驗證
以範例來做推演:

輸入多項式

P1:3x^2 + 2x^1 + 1

P2:3x^1

加法:

(3x^2 + 2x^1 + 1) + (3x^1) = 3x^2 + 5x^1 + 1

減法:

(3x^2 + 2x^1 + 1) - (3x^1) = 3x^2 - 1x^1 + 1

乘法:

(3x^2 + 2x^1 + 1) * (3x^1) = 9x^3 + 6x^2 + 3x^1

當x = 2時，代入多項式運算

P1(2) = (3(2)^2 + 2(2)^1 + 1)= 12 + 4 + 1 = 17

P2(2) = 3(2)^1 = 6

sum(2) = (3(2)^2 + 2(2)^1 + 1) + (3(2)^1) = 3(2)^2 + 5(2)^1 + 1 = 23

Difference(2) = (3(2)^2 + 2(2)^1 + 1) - (3(2)^1) = 3(2)^2 - 1(2)^1 + 1 = 11

Product(2) = (3(2)^2 + 2(2)^1 + 1) * (3(2)^1) = 9(2)^3 + 6(2)^2 + 3(2)^1 = 102
