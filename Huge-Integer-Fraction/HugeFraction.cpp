#include "HugeFraction.h"


//constructors******************************
HugeFraction::HugeFraction() 
	: Numerator(0), Denominator(1) 
{
}

HugeFraction::HugeFraction(const HugeInteger& num, const HugeInteger& den)
    : Numerator(num), Denominator(den) 
{
    Reduce();
}

HugeFraction::HugeFraction(const HugeFraction& HF)
    : Numerator(HF.Numerator), Denominator(HF.Denominator)
{
}

HugeFraction::HugeFraction(const  string& decimalStr) 
{
    fromDecimalString(decimalStr);
}

//FUNCTIONS*************************************
void HugeFraction::Reduce() 
{
    if (this->Denominator < HugeInteger(0)) 
    {
        this->Numerator = -Numerator;
        this->Denominator = -Denominator;
    }
    HugeInteger gcd = GCD(Numerator, Denominator);
    if (gcd > HugeInteger(1)) 
    {
        this->Numerator /= gcd;
        this->Denominator /= gcd;
    }
}


void HugeFraction::fromDecimalString(const string& decimalStr)
{
    bool IsNegative = false;
    int start = 0;
    if (!decimalStr.empty() && decimalStr[0] == '-') 
    {
        IsNegative = true;
        start = 1;
    }
    else if (!decimalStr.empty() && decimalStr[0] == '+') 
    {
        start = 1;
    }

    int dot = decimalStr.find('.', start);
    int lparen = decimalStr.find('(', start);
    int rparen = decimalStr.find(')', start);

    string Integer, Fraction, Recurring;
    if (dot == string::npos) 
    {
        Integer = decimalStr.substr(start);
    }
    else 
    {
        Integer = decimalStr.substr(start, dot - start);
        if (lparen != string::npos && rparen != string::npos && lparen > dot) 
        {
            Fraction = decimalStr.substr(dot + 1, lparen - dot - 1);
            Recurring = decimalStr.substr(lparen + 1, rparen - lparen - 1);
        }
        else 
        {
            Fraction = decimalStr.substr(dot + 1);
        }
    }

    Integer = TrimLeadingZeros(Integer);

    HugeInteger numerator(0), denominator(1);

    if (!Recurring.empty()) 
    {
        string FullNumber = Integer + Fraction + Recurring;
        string NonRecurNum = Integer + Fraction;

        numerator = HugeInteger(FullNumber) - HugeInteger(NonRecurNum);

        string denStr(Recurring.size(), '9');
        denStr += string(Fraction.size(), '0');
        denominator = HugeInteger(denStr);

        if (Integer != "0") 
        {
            numerator += HugeInteger(Integer) * denominator;
        }
    }
    else if (!Fraction.empty())
    {
        string numStr = Integer + Fraction;
        numerator = HugeInteger(numStr);

        string denStr = "1" + string(Fraction.size(), '0');
        denominator = HugeInteger(denStr);
    }
    else
    {
        numerator = HugeInteger(Integer);
        denominator = HugeInteger(1);
    }

    if (IsNegative)
    {
        numerator = -numerator;
    }

    Numerator = numerator;
    Denominator = denominator;
    Numerator.Trim();
    Denominator.Trim();
    Reduce();
}



//OPERATORS************************************

HugeFraction HugeFraction::operator+(const HugeFraction& HF) const
{
    HugeInteger n = this->Numerator * HF.Denominator + HF.Numerator * this->Denominator;
    HugeInteger d = this->Denominator * HF.Denominator;
    HugeFraction R(n, d);
    R.Reduce();
    return R;
}
HugeFraction HugeFraction::operator-(const HugeFraction& HF) const
{
    HugeInteger n = this->Numerator * HF.Denominator - HF.Numerator * this->Denominator;
    HugeInteger d = this->Denominator * HF.Denominator;
    HugeFraction R(n, d);
    R.Reduce();
    return R;
}
HugeFraction HugeFraction::operator*(const HugeFraction& HF) const
{
    HugeInteger n = Numerator * HF.Numerator;
    HugeInteger d = Denominator * HF.Denominator;
    HugeFraction R(n, d);
    R.Reduce();
    return R;
}
HugeFraction HugeFraction::operator/(const HugeFraction& HF) const
{
    HugeInteger n = Numerator * HF.Denominator;
    HugeInteger d = Denominator * HF.Numerator;
    HugeFraction R(n, d);
    R.Reduce();
    return R;
}

const HugeFraction& HugeFraction::operator+=(const HugeFraction& HF)
{
    return *this = *this + HF;
}
const HugeFraction& HugeFraction::operator-=(const HugeFraction& HF)
{
    return *this = *this - HF;
}
const HugeFraction& HugeFraction::operator*=(const HugeFraction& HF)
{
    return *this = *this * HF;
}
const HugeFraction& HugeFraction::operator/=(const HugeFraction& HF)
{
    return *this = *this / HF;
}

bool HugeFraction::operator==(const HugeFraction& HF) const
{
    return Numerator == HF.Numerator && Denominator == HF.Denominator;
}
bool HugeFraction::operator!=(const HugeFraction& HF) const
{
    return !(*this == HF);
}
bool HugeFraction::operator<(const HugeFraction& HF) const
{
    return (Numerator * HF.Denominator) < (HF.Numerator * Denominator);
}
bool HugeFraction::operator<=(const HugeFraction& HF) const
{
    return !(*this > HF);
}
bool HugeFraction::operator>(const HugeFraction& HF) const
{
    return (Numerator * HF.Denominator) > (HF.Numerator * Denominator);
}
bool HugeFraction::operator>=(const HugeFraction& HF) const
{
    return !(*this < HF);
}

HugeFraction HugeFraction::operator-() const
{
    return HugeFraction(-Numerator, Denominator);
}

const HugeFraction& HugeFraction::operator=(const HugeFraction& HF)
{
    if (this != &HF) 
    {
        Numerator = HF.Numerator;
        Denominator = HF.Denominator;
    }
    return *this;
}