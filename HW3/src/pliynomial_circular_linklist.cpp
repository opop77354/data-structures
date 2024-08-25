#include <iostream>
#include <cmath> 
using namespace std;

struct Term {
    float coef;
    int exp;
    Term* next;
};

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

void Polynomial::newTerm(float coef, int exp) {
    if (coef == 0) return;  // 無需添加零係數項

    Term* newTerm = new Term{ coef, exp, nullptr };
    if (!first) {
        first = newTerm;
        newTerm->next = first; // 環狀串列
    }
    else {
        Term* current = first;
        Term* prev = nullptr;

        // 尋找插入新節點或更新現有節點的正確位置
        do {
            if (current->exp == exp) {
                current->coef += coef;
                delete newTerm;
                if (current->coef == 0) {  // 如果係數為零則刪除項
                    if (current == first) {
                        // 如果是唯一項，則清除多項式
                        if (current->next == first) {
                            delete current;
                            first = nullptr;
                        }
                        else {
                            //找到最後一個節點並更新鏈結
                            Term* last = first;
                            while (last->next != first) {
                                last = last->next;
                            }
                            last->next = current->next;
                            first = current->next;
                            delete current;
                        }
                    }
                    else {
                        prev->next = current->next;
                        delete current;
                    }
                }
                return;
            }
            prev = current;
            current = current->next;
        } while (current != first);

        // 在正確位置插入新節點
        prev->next = newTerm;
        newTerm->next = first;
    }
}

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


const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this == &a) return *this;

    clear();
    copy(a);
    return *this;
}

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

Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial negB;
    Term* current = b.first;
    do {
        negB.newTerm(-current->coef, current->exp);
        current = current->next;
    } while (current != b.first);

    return *this + negB;
}

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

float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    Term* current = first;
    do {
        result += current->coef * pow(x, current->exp);
        current = current->next;
    } while (current != first);
    return result;
}

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

