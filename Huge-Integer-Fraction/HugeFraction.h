#pragma once
#include"HugeInteger.h"
class HugeFraction
{
	HugeInteger Numerator;
	HugeInteger Denominator;

    static string TrimLeadingZeros(const string& str) 
    {
        int i = 0;
        while (i < str.size() && str[i] == '0') 
        {
            i++;
        }
        return i == str.size() ? "0" : str.substr(i);
    }

public:
	//CONSTRUCTORS
	HugeFraction();
    HugeFraction(const HugeInteger& num, const HugeInteger& den);
    HugeFraction(const HugeFraction& other);
    HugeFraction(const  string& decimalStr);

	//FUNCTIONS
    static HugeInteger GCD(HugeInteger a, HugeInteger b) 
    {
        a = (a < HugeInteger(0)) ? -a : a;
        b = (b < HugeInteger(0)) ? -b : b;
        while (b != HugeInteger::Zero()) 
        {
            HugeInteger t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    void Reduce();

    void fromDecimalString(const string& decimalStr);

	//OPERATORS
    friend ostream& operator<<(ostream& out, const HugeFraction& f);

    friend istream& operator>>(istream& in, HugeFraction& f);

    HugeFraction operator+(const HugeFraction& HF) const;
    HugeFraction operator-(const HugeFraction& HF) const;
    HugeFraction operator*(const HugeFraction& HF) const;
    HugeFraction operator/(const HugeFraction& HF) const;

    const HugeFraction& operator+=(const HugeFraction& HF);
    const HugeFraction& operator-=(const HugeFraction& HF);
    const HugeFraction& operator*=(const HugeFraction& HF);
    const HugeFraction& operator/=(const HugeFraction& HF);

    bool operator==(const HugeFraction& HF) const;
    bool operator!=(const HugeFraction& HF) const;
    bool operator<(const HugeFraction& HF) const;
    bool operator<=(const HugeFraction& HF) const;
    bool operator>(const HugeFraction& HF) const;
    bool operator>=(const HugeFraction& HF) const;

    HugeFraction operator-() const;

    const HugeFraction& operator=(const HugeFraction& HF);
};

