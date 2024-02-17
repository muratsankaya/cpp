#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    friend bool operator==(const Polynomial& lsh, const Polynomial& rhs);
    struct Node;
public:
    Polynomial();
    Polynomial(const std::vector<int>& vectorOfCoefs);
    Polynomial(const Polynomial& rhs);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& rhs);
    void deepCopy(const Polynomial& rhs);
    void removeAll();
    Polynomial& operator+=(const Polynomial& rhs);
    int evaluate(int input);
private:
    Node* headptr;
    int degree;
    void removeZeros();
    int power(int val, int degree);
};
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif
