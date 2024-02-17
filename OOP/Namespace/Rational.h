
#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace CS2124 {
    void setSign(int& n, int& d);
    int greatestCommonDivisor(int x, int y);

    class Rational {
        friend std::ostream& operator<<(std::ostream& os, const Rational& num);
        friend std::istream& operator>>(std::istream& is, Rational& num);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);
    public:
        Rational(int n = 0, int d = 1);
        Rational& operator+=(const Rational& rhs);
        Rational& operator++();
        Rational operator++(int dummy);
        explicit operator bool() const;
        Rational& operator-=(const Rational& rhs);
    private:
        int numerator, denominator;
        void setSignAndNormalize();
    };

    Rational operator+(const Rational& lhs, const Rational& rhs);
    Rational& operator--(Rational& rhs);
    Rational operator--(Rational& lhs, int dummy);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    bool operator<=(const Rational& lhs, const Rational& rhs);
    bool operator>(const Rational& lhs, const Rational& rhs);
    bool operator>=(const Rational& lhs, const Rational& rhs);

}

#endif