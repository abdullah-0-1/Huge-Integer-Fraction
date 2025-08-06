#include <iostream>
#include"HugeInteger.h"
#include"HugeFraction.h"
using namespace std;

ostream& operator<<(ostream& out, const HugeInteger HI)
{
	out << (HI.IsNeg ? '-' : ' ');
	for (int di = HI.Ds.size() - 1; di >= 0; di--)
	{
		out << HI.Ds[di];
	}
	return out;
}

istream& operator>>(istream& in, HugeInteger& HI)
{
	string S;
	in >> S;
	int si = 0;
	HI.IsNeg = false;
	if (!S.empty() && (S[si] == '+' || S[si] == '-')) 
	{
		HI.IsNeg = (S[si] == '-');
		si++;
	}
	HI.Ds.resize(S.size() - si);
	for (int di = 0; di < HI.Ds.size(); di++) 
	{
		HI.Ds[di] = S[si + HI.Ds.size() - 1 - di] - '0';
	}
	return in;
}

ostream& operator<<( ostream& out, const HugeFraction& f) 
{
    out << f.Numerator << "/" << f.Denominator;
    return out;
}

istream& operator>>( istream& in, HugeFraction& f) 
{
    string s;
    in >> s;
    f.fromDecimalString(s);
    return in;
}




void Menu()
{
    cout << "\n===== HugeInteger Operator Testing Menu =====\n";
    cout << "1. Test == operator\n";
    cout << "2. Test < operator\n";
    cout << "3. Test > operator\n";
    cout << "4. Test <= operator\n";
    cout << "5. Test >= operator\n";
    cout << "6. Test + operator\n";
    cout << "7. Test - operator\n";
    cout << "8. Test * operator\n";
    cout << "9. Test / operator\n";
    cout << "10. Test % operator\n";
    cout << "11. Test += operator\n";
    cout << "12. Test -= operator\n";
    cout << "13. Test *= operator\n";
    cout << "14. Test /= operator\n";
    cout << "15. Test %= operator\n";
    cout << "16. Test prefix ++ operator\n";
    cout << "17. Test prefix -- operator\n";
    cout << "18. Test postfix ++ operator\n";
    cout << "19. Test postfix -- operator\n";
    cout << "20. Display all HugeIntegers\n";
    cout << "0. Exit to main menu\n";
}

int HIntegers()
{
    ifstream rdr("HIs.txt");
    HugeInteger** I;
    int NumOfHI = 0;
    rdr >> NumOfHI;
    rdr.ignore();
    I = new HugeInteger * [NumOfHI];
    for (int i = 0; i < NumOfHI; i++)
    {
        I[i] = new HugeInteger();
        rdr >> *I[i];
    }
    cout << "HUGE INTEGER NUMBERS: \n";
    ofstream fout("Output.txt");
    for (int i = 0; i < NumOfHI; i++)
    {
        cout << "[" << i << "]: " << *I[i] << endl;
        fout << *I[i] << endl;
    }

    int choice = -1;
    int idx1 = 0, idx2 = 1;
    HugeInteger temp;

    while (choice != 0)
    {
        Menu();
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 0) break;

        if (choice >= 1 && choice <= 15)
        {
            cout << "Enter index of first HugeInteger (0 to " << NumOfHI - 1 << "): ";
            cin >> idx1;
            cout << "Enter index of second HugeInteger (0 to " << NumOfHI - 1 << "): ";
            cin >> idx2;
            if (idx1 < 0 || idx1 >= NumOfHI || idx2 < 0 || idx2 >= NumOfHI) 
            {
                cout << "Invalid indices!\n";
                continue;
            }
        }
        else if (choice >= 16 && choice <= 19)
        {
            cout << "Enter index of HugeInteger (0 to " << NumOfHI - 1 << "): ";
            cin >> idx1;
            if (idx1 < 0 || idx1 >= NumOfHI) 
            {
                cout << "Invalid index!\n";
                continue;
            }
        }

        switch (choice)
        {
        case 1:
            cout << (*I[idx1] == *I[idx2] ? "Equal\n" : "Not Equal\n");
            break;
        case 2:
            cout << (*I[idx1] < *I[idx2] ? "First < Second\n" : "First >= Second\n");
            break;
        case 3:
            cout << (*I[idx1] > *I[idx2] ? "First > Second\n" : "First <= Second\n");
            break;
        case 4:
            cout << (*I[idx1] <= *I[idx2] ? "First <= Second\n" : "First > Second\n");
            break;
        case 5:
            cout << (*I[idx1] >= *I[idx2] ? "First >= Second\n" : "First < Second\n");
            break;
        case 6:
            cout << "Sum: " << (*I[idx1] + *I[idx2]) << endl;
            break;
        case 7:
            cout << "Difference: " << (*I[idx1] - *I[idx2]) << endl;
            break;
        case 8:
            cout << "Product: " << (*I[idx1] * *I[idx2]) << endl;
            break;
        case 9:
            if (*I[idx2] == HugeInteger(0))
                cout << "Division by zero!\n";
            else
                cout << "Quotient: " << (*I[idx1] / *I[idx2]) << endl;
            break;
        case 10:
            if (*I[idx2] == HugeInteger(0))
                cout << "Division by zero!\n";
            else
                cout << "Remainder: " << (*I[idx1] % *I[idx2]) << endl;
            break;
        case 11:
            temp = *I[idx1];
            temp += *I[idx2];
            cout << "After += : " << temp << endl;
            break;
        case 12:
            temp = *I[idx1];
            temp -= *I[idx2];
            cout << "After -= : " << temp << endl;
            break;
        case 13:
            temp = *I[idx1];
            temp *= *I[idx2];
            cout << "After *= : " << temp << endl;
            break;
        case 14:
            if (*I[idx2] == HugeInteger(0))
                cout << "Division by zero!\n";
            else {
                temp = *I[idx1];
                temp /= *I[idx2];
                cout << "After /= : " << temp << endl;
            }
            break;
        case 15:
            if (*I[idx2] == HugeInteger(0))
                cout << "Division by zero!\n";
            else {
                temp = *I[idx1];
                temp %= *I[idx2];
                cout << "After %= : " << temp << endl;
            }
            break;
        case 16:
            temp = *I[idx1];
            ++temp;
            cout << "After prefix ++: " << temp << endl;
            break;
        case 17:
            temp = *I[idx1];
            --temp;
            cout << "After prefix --: " << temp << endl;
            break;
        case 18:
            temp = *I[idx1];
            temp++;
            cout << "After postfix ++: " << temp << endl;
            break;
        case 19:
            temp = *I[idx1];
            temp--;
            cout << "After postfix --: " << temp << endl;
            break;
        case 20:
            cout << "All HugeIntegers:\n";
            for (int i = 0; i < NumOfHI; i++)
                cout << "[" << i << "]: " << *I[i] << endl;
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    }

    for (int i = 0; i < NumOfHI; i++)
    {
        delete I[i];
    }
    delete[] I;
    return 0;
}

void FractionMenu()
{
    cout << "\n===== HugeFraction Operator Testing Menu =====\n";
    cout << "1. Test == operator\n";
    cout << "2. Test < operator\n";
    cout << "3. Test > operator\n";
    cout << "4. Test <= operator\n";
    cout << "5. Test >= operator\n";
    cout << "6. Test + operator\n";
    cout << "7. Test - operator\n";
    cout << "8. Test * operator\n";
    cout << "9. Test / operator\n";
    cout << "10. Test += operator\n";
    cout << "11. Test -= operator\n";
    cout << "12. Test *= operator\n";
    cout << "13. Test /= operator\n";
    cout << "14. Test unary - operator\n";
    cout << "15. Display all HugeFractions\n";
    cout << "0. Exit to main menu\n";
}

int HFractions()
{
    ifstream rdr("HFs.txt");
    if (!rdr)
    {
        cout << "Could not open input file!\n";
        return 1;
    }

    int NumOfFrac = 0;
    rdr >> NumOfFrac;
    rdr.ignore();

    HugeFraction** F = new HugeFraction * [NumOfFrac];
    for (int i = 0; i < NumOfFrac; i++)
    {
        F[i] = new HugeFraction();
        rdr >> *F[i];
    }
    cout << "HUGE FRACTION NUMBERS: \n";
    ofstream fout("Output.txt");
    for (int i = 0; i < NumOfFrac; i++)
    {
        cout << "[" << i << "]: " << *F[i] << endl;
        fout << *F[i] << endl;
    }
    int choice = -1, idx1 = 0, idx2 = 1;
    HugeFraction temp;

    while (choice != 0)
    {
        FractionMenu();
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 0) break;

        if (choice >= 1 && choice <= 13)
        {
            cout << "Enter index of first HugeFraction (0 to " << NumOfFrac - 1 << "): ";
            cin >> idx1;
            cout << "Enter index of second HugeFraction (0 to " << NumOfFrac - 1 << "): ";
            cin >> idx2;
            if (idx1 < 0 || idx1 >= NumOfFrac || idx2 < 0 || idx2 >= NumOfFrac)
            {
                cout << "Invalid indices!\n";
                continue;
            }
        }
        else if (choice == 14)
        {
            cout << "Enter index of HugeFraction (0 to " << NumOfFrac - 1 << "): ";
            cin >> idx1;
            if (idx1 < 0 || idx1 >= NumOfFrac)
            {
                cout << "Invalid index!\n";
                continue;
            }
        }

        switch (choice)
        {
        case 1:
            cout << (*F[idx1] == *F[idx2] ? "Equal\n" : "Not Equal\n");
            break;
        case 2:
            cout << (*F[idx1] < *F[idx2] ? "First < Second\n" : "First >= Second\n");
            break;
        case 3:
            cout << (*F[idx1] > *F[idx2] ? "First > Second\n" : "First <= Second\n");
            break;
        case 4:
            cout << (*F[idx1] <= *F[idx2] ? "First <= Second\n" : "First > Second\n");
            break;
        case 5:
            cout << (*F[idx1] >= *F[idx2] ? "First >= Second\n" : "First < Second\n");
            break;
        case 6:
            cout << "Sum: " << (*F[idx1] + *F[idx2]) << endl;
            break;
        case 7:
            cout << "Difference: " << (*F[idx1] - *F[idx2]) << endl;
            break;
        case 8:
            cout << "Product: " << (*F[idx1] * *F[idx2]) << endl;
            break;
        case 9:
            if (*F[idx2] == HugeFraction(HugeInteger(0), HugeInteger(1)))
                cout << "Division by zero!\n";
            else
                cout << "Quotient: " << (*F[idx1] / *F[idx2]) << endl;
            break;
        case 10:
            temp = *F[idx1];
            temp += *F[idx2];
            cout << "After += : " << temp << endl;
            break;
        case 11:
            temp = *F[idx1];
            temp -= *F[idx2];
            cout << "After -= : " << temp << endl;
            break;
        case 12:
            temp = *F[idx1];
            temp *= *F[idx2];
            cout << "After *= : " << temp << endl;
            break;
        case 13:
            if (*F[idx2] == HugeFraction(HugeInteger(0), HugeInteger(1)))
                cout << "Division by zero!\n";
            else {
                temp = *F[idx1];
                temp /= *F[idx2];
                cout << "After /= : " << temp << endl;
            }
            break;
        case 14:
            temp = -*F[idx1];
            cout << "After unary - : " << temp << endl;
            break;
        case 15:
            cout << "All HugeFractions:\n";
            for (int i = 0; i < NumOfFrac; i++)
                cout << "[" << i << "]: " << *F[i] << endl;
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    }

    for (int i = 0; i < NumOfFrac; i++)
        delete F[i];
    delete[] F;
    return 0;
}

void Options()
{
    cout << "Which Part To Test\n";
    cout << "1) Huge Integers\n";
    cout << "2) Huge Fractions\n";
    cout << "0) Exit Program\n";
}

int main()
{
    int choice = -1;
    while (choice != 0)
    {
        Options();
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            HIntegers();
            break;
        case 2:
            system("cls");
            HFractions();
            break;
        case 0:
            cout << "\nEXITING...\n";
            exit(1);
            break;
        default:
            cout << "\nINVALID INPUT...\n";
            break;
        }
        system("cls");
    }
    return 0;
}