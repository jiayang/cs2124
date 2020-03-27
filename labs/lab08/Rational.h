#ifndef RATIONALS

#define RATIONALS

#include <iostream>

namespace CS2124 {
    class Rational {
        friend bool operator==(const Rational& a, const Rational& b);
        friend bool operator<(const Rational& a, const Rational& b);
        friend std::ostream& operator<<(std::ostream& os,
                                        const Rational& rational);
        friend std::istream& operator>>(std::istream& is,
                                        Rational& rational);
    public:
        Rational(int numerator=0, int denominator=1);
        void simplify();
        
        Rational& operator+=(const Rational& other);
        
        Rational& operator++();
        
        Rational operator++(int dummy);
        
        explicit operator bool() const;
        
    private:
        //Rationals are written as p/q
        int p;
        int q;
        
    };

    Rational operator+(const Rational& a, const Rational& b);
    
    //a == b
    bool operator==(const Rational& a, const Rational& b);
    
    //a != b
    bool operator!=(const Rational& a, const Rational& b);
    
    //--a
    Rational& operator--(Rational& a);
    
    //a--
    Rational operator--(Rational& a, int dummy);
    
    //a < b
    bool operator<(const Rational& a, const Rational& b);
    
    //a > b
    bool operator>(const Rational& a, const Rational& b);
    
    //a <= b
    bool operator<=(const Rational& a, const Rational& b);
    
    //a >= b
    bool operator>=(const Rational& a, const Rational& b);
}

#endif
