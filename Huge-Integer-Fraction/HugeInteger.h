#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class HugeInteger
{
	vector<int> Ds;
	bool IsNeg;

	//UTILITY FUNCTIONS
	HugeInteger ADDQuantityWise(const HugeInteger& H2) const;
	HugeInteger SUBQuantityWise(const HugeInteger& H2) const;
	bool LessThanQuantityWise(const HugeInteger& H2) const;
	bool GreaterThanQuantityWise(const HugeInteger& H2) const;
	bool EqualQuantityWise(const HugeInteger& H2) const;




public:

	//CONSTRUCTORS
	HugeInteger();
	HugeInteger(ifstream& rdr);
	HugeInteger(int S);
    HugeInteger(const string& Str);
	HugeInteger(const HugeInteger& H2);

	//FUNCTIONS
	void Trim();
	static HugeInteger One()
	{
		HugeInteger HI(1);
		HI[0]++;
		return HI;
	}

	static HugeInteger Zero()
	{
		HugeInteger HI(1);
		HI[0]=0;
		return HI;
	}
	
	//OPERATORS
	const HugeInteger& operator=(const HugeInteger& HI);
	int operator[] (int i)const;
	int& operator[] (int i);
	HugeInteger operator+ (const HugeInteger& H2)const;
	const HugeInteger& operator+= (const HugeInteger& H2);
	HugeInteger operator- (const HugeInteger& H2)const;
	const HugeInteger& operator-= (const HugeInteger& H2);
	HugeInteger operator- ()const;
	HugeInteger& operator++();
	HugeInteger& operator--();
	HugeInteger operator++(int);
	HugeInteger operator--(int);
	bool operator<(const HugeInteger& HI)const;
	bool operator>(const HugeInteger& HI)const;
	bool operator<=(const HugeInteger& HI)const;
	bool operator>=(const HugeInteger& HI)const;
	bool operator==(const HugeInteger& HI)const;
	bool operator!=(const HugeInteger& HI)const;

	HugeInteger operator* (const HugeInteger& H2)const;
	const HugeInteger& operator*=(const HugeInteger& H2);
	HugeInteger operator/ (const HugeInteger& H2) const;
	const HugeInteger& operator/= (const HugeInteger& H2);
	HugeInteger operator% (const HugeInteger& H2) const;
	const HugeInteger& operator%= (const HugeInteger& H2);

	friend ostream& operator<<(ostream& out, const HugeInteger HI);
	friend istream& operator>>(istream& in, HugeInteger& HI);
};

