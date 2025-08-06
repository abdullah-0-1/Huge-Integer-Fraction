#include "HugeInteger.h"
HugeInteger::HugeInteger()
{
	IsNeg = false;
    Ds.resize(1);
}
HugeInteger::HugeInteger(ifstream& rdr)
{
	string S;
	rdr >> S;
    int si=0;
    IsNeg=false;
	if (S[si] == '+' || S[si] == '-')
	{
		this->IsNeg = ((S[si] == '-') ? true : false);
		si++;
	}
	Ds.resize(S.size()-si);
	for (int di = 0; di < this->Ds.size(); di++)
	{
		Ds[di] = S[si + Ds.size() - 1 - di] - '0';
	}

}
HugeInteger::HugeInteger(int S)
{
	IsNeg = false;
	Ds.resize(S,0);
}
HugeInteger::HugeInteger(const string& Str)
{
    int si = 0;
    IsNeg = false;
    if (!Str.empty() && (Str[si] == '+' || Str[si] == '-'))
    {
        IsNeg = (Str[si] == '-');
        si++;
    }
    Ds.resize(Str.size() - si);
    for (int di = 0; di < Ds.size(); di++)
    {
        Ds[di] = Str[si + Ds.size() - 1 - di] - '0';
    }
}
HugeInteger::HugeInteger(const HugeInteger& H2)
{
    Ds = H2.Ds;
    IsNeg = H2.IsNeg;
}

//FUNCTIONS****************************
HugeInteger HugeInteger:: ADDQuantityWise(const HugeInteger& H2) const
{
    HugeInteger R(max(Ds.size(), H2.Ds.size()) + 1);
    int Carry = 0;
    for (int i = 0; i < R.Ds.size(); i++)
    {
        int sum = (*this)[i] + H2[i] + Carry;
        R[i] = sum % 10;
        Carry = sum / 10;
    }
    R.Trim();
    return R;
}

HugeInteger HugeInteger:: SUBQuantityWise(const HugeInteger& H2) const
{
    HugeInteger R(this->Ds.size());
    int Carry = 0;
    for (int i = 0; i < R.Ds.size(); i++)
    {
        int sum = (*this)[i] - H2[i] - Carry;
        if (sum<0)
        {
            sum += 10;
            Carry = 1;
        }
        else
        {
            Carry = 0;
        }
        R[i] = sum;
    }
    R.Trim();
    return R;
}
bool HugeInteger::LessThanQuantityWise(const HugeInteger& H2) const
{
    if (this->Ds.size() > H2.Ds.size())
    {
        return false;
    }
    if (this->Ds.size() < H2.Ds.size())
    {
        return true;
    }
    for (int i = this->Ds.size()-1; i >=0 ; i--)
    {
        if ((*this)[i] > H2[i])
        {
            return false;
        }
        if ((*this)[i] < H2[i])
        {
            return true;
        }
    }
    return false;
}
bool HugeInteger::GreaterThanQuantityWise(const HugeInteger& H2) const
{
    return H2.LessThanQuantityWise(*this);
}
bool HugeInteger::EqualQuantityWise(const HugeInteger& H2) const
{
    return !(LessThanQuantityWise(H2)) && !(GreaterThanQuantityWise(H2));
}


// UTILITY FUNCTIONS**************************
void HugeInteger::Trim()
{
    while (Ds.size() > 1 && Ds.back() == 0)
    {
        Ds.pop_back();
    }
}



//OPERATORS****************************

const HugeInteger& HugeInteger::operator=(const HugeInteger& HI)
{
    if (this != &HI) {
        Ds = HI.Ds;
        IsNeg = HI.IsNeg;
    }
    return *this;
}

int HugeInteger::operator[] (int i)const
{
    if (i < Ds.size())
    {
        return Ds[i];
    }
    else
    {
        return 0;
    }
}
int& HugeInteger::operator[] (int i)
{
    return Ds[i];
}

HugeInteger HugeInteger::operator+ (const HugeInteger& H2)const
{
    if (this->IsNeg == H2.IsNeg)
    {
        if (this->GreaterThanQuantityWise(H2))
        {
            HugeInteger R = this->ADDQuantityWise(H2);
            R.IsNeg = this->IsNeg;
            return R;
        }
        else
        {
            HugeInteger R = H2.ADDQuantityWise(*this);
            R.IsNeg = this->IsNeg;
            return R;
        }
    }
    else
    {
        if (this->GreaterThanQuantityWise(H2))
        {
            HugeInteger R = this->SUBQuantityWise(H2);
            R.IsNeg = this->IsNeg;
            return R;
        }
        else
        {
            HugeInteger R = H2.SUBQuantityWise(*this);
            R.IsNeg = H2.IsNeg;
            return R;
        }
    }
}

HugeInteger HugeInteger::operator- (const HugeInteger& H2)const
{
    HugeInteger R = -H2;
    R = R + (*this);
    return R;
}
HugeInteger HugeInteger::operator- ()const
{
    HugeInteger R = *this;
    R.IsNeg = !this->IsNeg;
    return R;
}

const HugeInteger& HugeInteger:: operator+= (const HugeInteger& H2)
{
    return *this = *this + H2;
}
const HugeInteger& HugeInteger::operator-= (const HugeInteger& H2)
{
    return *this = *this - H2;
}

HugeInteger& HugeInteger::operator++()
{
    *this += One();
    return *this;
}
HugeInteger& HugeInteger::operator--() 
{
    *this -= One();
    return *this;
}

HugeInteger HugeInteger::operator++(int) 
{
    HugeInteger temp = *this;
    *this += One();
    return temp;
}
HugeInteger HugeInteger::operator--(int) 
{
    HugeInteger temp = *this;
    *this -= One();
    return temp;
}

bool HugeInteger::operator<(const HugeInteger& HI)const
{
    if (this->IsNeg != HI.IsNeg)
    {
        return this->IsNeg; // - , +
    }

    if (!this->IsNeg) //+,+
    {
        return this->LessThanQuantityWise(HI);
    }
    else // -,-
    {
        return HI.LessThanQuantityWise(*this);
    }
}
bool HugeInteger::operator>(const HugeInteger& HI)const
{
    if (this->IsNeg != HI.IsNeg)
    {
        return HI.IsNeg; // +,-
    }

    if (!this->IsNeg) // +,+
    {
        return this->GreaterThanQuantityWise(HI);
    }
    else // -,-
    {
        return HI.GreaterThanQuantityWise(*this);
    }
}
bool HugeInteger::operator<=(const HugeInteger& HI)const
{
    return !(*this > HI);
}
bool HugeInteger::operator>=(const HugeInteger& HI)const
{
    return !(*this < HI);
}
bool HugeInteger::operator==(const HugeInteger& HI)const
{
    return this->IsNeg == HI.IsNeg && this->EqualQuantityWise(HI);
}

bool HugeInteger::operator!=(const HugeInteger& HI)const
{
    return !(*this == HI);
}

HugeInteger HugeInteger::operator* (const HugeInteger& H2)const
{
    HugeInteger Total = Zero();
    HugeInteger A = *this;
    A.IsNeg = false;
    HugeInteger B = H2;
    B.IsNeg = false;
    while (B > Zero())
    {
        HugeInteger Count = One();
        HugeInteger R = A;
        while (true)
        {
            if (Count + Count <= B)
            {
                Count += Count;
                R += R;
            }
            else
            {
                break;
            }
        }
        Total += R;
        B -= Count;
    }
    Total.IsNeg = (this->IsNeg != H2.IsNeg) && !(Total == Zero());
    return Total;
}
const HugeInteger& HugeInteger::operator*=(const HugeInteger& H2)
{
    return *this = *this * H2;
}

HugeInteger HugeInteger::operator/ (const HugeInteger& H2) const
{
    if (H2 == HugeInteger::Zero()) 
    {
        cerr << "Division By Zero";
        return HugeInteger::Zero();
    }

    HugeInteger A = *this;
    A.IsNeg = false;
    HugeInteger B = H2;
    B.IsNeg = false;

    HugeInteger quotient = Zero();
    HugeInteger remainder = A;

    while (remainder >= B)
    {
        HugeInteger Count = One();
        HugeInteger R = B;
        while (true)
        {
            if (R + R <= remainder)
            {
                R += R;
                Count += Count;
            }
            else
            {
                break;
            }
        }
        remainder -= R;
        quotient += Count;
    }

    quotient.IsNeg = (this->IsNeg != H2.IsNeg) && !(quotient == Zero());
    return quotient;
}

const HugeInteger& HugeInteger::operator/= (const HugeInteger& H2)
{
    *this = *this / H2;
    return *this;
}

HugeInteger HugeInteger::operator%(const HugeInteger& H2) const
{
    if (H2 == HugeInteger::Zero())
    {
        cerr << "Modulo By Zero";
        return HugeInteger::Zero();
    }

    HugeInteger A = *this;
    A.IsNeg = false;
    HugeInteger B = H2;
    B.IsNeg = false;

    HugeInteger remainder = A;

    while (remainder >= B)
    {
        HugeInteger Count = One();
        HugeInteger R = B;
        while (true)
        {
            if (R + R <= remainder)
            {
                R += R;
                Count += Count;
            }
            else
            {
                break;
            }
        }
        remainder -= R;
    }

    remainder.IsNeg = this->IsNeg && !(remainder == Zero());
    return remainder;
}

const HugeInteger& HugeInteger::operator%=(const HugeInteger& H2)
{
    *this = *this % H2;
    return *this;
}