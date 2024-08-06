#include <iostream>
#include <cmath> 

using namespace std;

class Term {
public:
    float coef;
    int exp;
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
public:
    Polynomial(int d = 0);
    ~Polynomial();

    Polynomial(const Polynomial& other); 
    Polynomial& operator=(const Polynomial& other); 

    void AddTerm(float coef, int exp);
    Polynomial Add(const Polynomial& b) const;
    Polynomial Mult(const Polynomial& b) const;
    float Eval(float x) const;
    void Output() const;

private:
    Term* terms;
    int size; 
    int capacity;

    void Resize(int new_capacity);
    void AddOrUpdateTerm(float coef, int exp);
};

Polynomial::Polynomial(int d) : size(0), capacity(d) {
    terms = new Term[capacity];
}

Polynomial::~Polynomial() {
    delete[] terms;
}

Polynomial::Polynomial(const Polynomial& other) : size(other.size), capacity(other.capacity) {
    terms = new Term[capacity];
    for (int i = 0; i < size; ++i) {
        terms[i] = other.terms[i];
    }
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] terms;
        size = other.size;
        capacity = other.capacity;
        terms = new Term[capacity];
        for (int i = 0; i < size; ++i) {
            terms[i] = other.terms[i];
        }
    }
    return *this;
}

void Polynomial::Resize(int new_capacity) {
    Term* new_terms = new Term[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_terms[i] = terms[i];
    }
    delete[] terms;
    terms = new_terms;
    capacity = new_capacity;
}

void Polynomial::AddOrUpdateTerm(float c, int e) {
    for (int i = 0; i < size; ++i) {
        if (terms[i].exp == e) {
            terms[i].coef += c;
            if (terms[i].coef == 0) {
                
                for (int j = i; j < size - 1; ++j) {
                    terms[j] = terms[j + 1];
                }
                --size;
            }
            return;
        }
    }

    if (size == capacity) {
        Resize(capacity * 2);
    }
    terms[size++] = Term(c, e);
}

void Polynomial::AddTerm(float c, int e) {
    AddOrUpdateTerm(c, e);
}

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

float Polynomial::Eval(float x) const {
    float result = 0;
    for (int i = 0; i < size; ++i) {
        result += terms[i].coef * pow(x, terms[i].exp);
    }
    return result;
}

void Polynomial::Output() const {
    if (size == 0) {
        cout << "0";
        return;
    }

    for (int i = 0; i < size; ++i) {
        if (i > 0 && terms[i].coef > 0) cout << "+";
        cout << terms[i].coef;
        if (terms[i].exp != 0) cout << "x^" << terms[i].exp;
    }
    cout << endl;
}

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
