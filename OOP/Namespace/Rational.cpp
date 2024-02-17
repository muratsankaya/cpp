

#include "Rational.h"
#include <iostream>
#include <string>
using namespace std;

namespace CS2124 {

    void setSign(int& n, int& d) {
        if (d < 0) { n *= -1; d *= -1; }
    }

    int greatestCommonDivisor(int x, int y) {
        while (x != 0) {
            int initx = x;
            x = y % x;
            y = initx;
        } if (y < 0) y *= -1; return y;
    }

    ostream& operator<<(ostream& os, const Rational& num) {
        os << num.numerator << '/' << num.denominator; return os;
    }

    istream& operator>>(istream& is, Rational& num) {
        int n, d;
        is >> n;
        char c;
        is >> c;
        is >> d;
        num.numerator = n; num.denominator = d;
        num.setSignAndNormalize();
        return is;
    }

    bool operator==(const Rational& lhs, const Rational& rhs) {
        return (lhs.numerator == rhs.numerator) && (rhs.denominator == lhs.denominator);
    }

    bool operator<(const Rational& lhs, const Rational& rhs) {
        return (lhs.numerator * rhs.denominator) < (rhs.numerator * lhs.denominator);
    }

    Rational::Rational(int n, int d) {
        if (d == 0) { cerr << "The denominator can not be 0\nInitilaztion failed\n"; return; }
        numerator = n;
        denominator = d;
        this->setSignAndNormalize();
    }

    Rational& Rational::operator+=(const Rational& rhs) {
        numerator = (numerator * rhs.denominator) + (rhs.numerator * denominator);
        denominator *= rhs.denominator;
        this->setSignAndNormalize();
        return *this;
    }

    Rational& Rational::operator++() {
        numerator += denominator;
        this->setSignAndNormalize();
        return *this;
    }

    Rational Rational::operator++(int dummy) {
        Rational original = *this;
        numerator += denominator;
        this->setSignAndNormalize();
        return original;
    }

    Rational::operator bool() const {
        return numerator;
    }

    Rational& Rational::operator-=(const Rational& rhs) {
        numerator = (numerator * rhs.denominator) - (rhs.numerator * denominator);
        denominator *= rhs.denominator;
        this->setSignAndNormalize();
        return *this;
    }

    void Rational::setSignAndNormalize() {
        setSign(numerator, denominator);
        int gdc = greatestCommonDivisor(numerator, denominator);
        numerator /= gdc; denominator /= gdc;
    }

    Rational operator+(const Rational& lhs, const Rational& rhs) {
        Rational res = lhs;
        res += rhs;
        return res;
    }

    Rational& operator--(Rational& rhs) {
        rhs -= 1;
        return rhs;
    }

    Rational operator--(Rational& lhs, int dummy) {
        Rational original = lhs;
        lhs -= 1;
        return original;
    }

    bool operator!=(const Rational& lhs, const Rational& rhs) {
        return !(lhs == rhs);
    }

    bool operator<=(const Rational& lhs, const Rational& rhs) {
        return (lhs == rhs) || (lhs < rhs);
    }

    bool operator>(const Rational& lhs, const Rational& rhs) {
        return !(lhs < rhs) && (lhs != rhs);
    }

    bool operator>=(const Rational& lhs, const Rational& rhs) {
        return (lhs == rhs) || (lhs > rhs);
    }

}