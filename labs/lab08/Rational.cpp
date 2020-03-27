#include "Rational.h"
using namespace std;

namespace CS2124 {
    int greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }
    
    Rational::Rational(int numerator, int denominator)
        : p(numerator), q(denominator) {
        simplify();
    }
    
    void Rational::simplify() {
        if (q < 0) {
            p *= -1;
            q *= -1;
        }
        int gcd = greatestCommonDivisor(p,q);
        p /= gcd;
        q /= gcd;
    }
    
    Rational& Rational::operator+=(const Rational& other) {
        p = p * other.q + q * other.p; //Cross multiply and add
        q *= other.q;
        simplify();
        return *this;
    }
    
    Rational& Rational::operator++() {
        p += q;
        simplify();
        return *this;
    }
    
    Rational Rational::operator++(int dummy) {
        Rational aCopy(*this);
        p += q;
        simplify();
        return aCopy;
    }
    
    Rational::operator bool() const {
        return p != 0;
    }
    
    //a + b
    Rational operator+(const Rational& a, const Rational& b) {
        Rational result(a);
        result += b;
        return a;
    }
    
    //a == b
    bool operator==(const Rational& a, const Rational& b) {
        return a.p == b.p && a.q == b.q;
    }
    
    //a != b
    bool operator!=(const Rational& a, const Rational& b) {
        return !(a == b);
    }
    
    //--a
    Rational& operator--(Rational& a) {
        a += -1;
        return a;
    }
    
    //a--
    Rational operator--(Rational& a, int dummy) {
        Rational aCopy(a);
        a += -1;
        return aCopy;
    }
    
    //a < b
    bool operator<(const Rational& a, const Rational& b) {
        //Cross multiply and compare
        return a.p * b.q < a.q * b.p;
    }
    
    //a > b
    bool operator>(const Rational& a, const Rational& b) {
        return !(a < b || a == b);
    }
    
    //a <= b
    bool operator<=(const Rational& a, const Rational& b) {
        return a < b || a == b;
    }
    
    //a >= b
    bool operator>=(const Rational& a, const Rational& b) {
        return a > b || a == b;
    }
    
    ostream& operator<<(ostream& os, const Rational& rational) {
        os << rational.p << "/" << rational.q;
        return os;
    }
    istream& operator>>(istream& is, Rational& rational) {
        int p,q;
        char slash;
        is >> p >> slash >> q;
        rational.p = p;
        rational.q = q;
        rational.simplify();
        return is;
    }
}
