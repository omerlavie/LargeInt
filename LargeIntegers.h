#include <string>
#ifndef EX1_FINAL_LARGEINTEGERS_H
#define EX1_FINAL_LARGEINTEGERS_H
using namespace std;


    class InfInt {
    private:
        string	            _number;
        string              _binNumber;
        bool	            _sign;
        unsigned long long  _length;

    public:
        //Constructors
        InfInt();
        InfInt(long int num);
        InfInt(string num);
        InfInt(char* c);
        InfInt(const InfInt &i);

        //seters, geters
        void setNumber(string newNum);
        void setSign(bool sign);
        bool getSign();
        bool getStrSign(string n);
        unsigned long long getLength();
        string getNumber();
        unsigned long long int getLength(long int n);

        //Conversion functions
        string convertDecToBin(string n);
        string convertBinToDec(string b);
        string toString(long int num);
        long int toLongInt(string s);

        //Operators
        InfInt operator+(const InfInt & other);
        InfInt operator-(const InfInt & other);
        InfInt operator*(const InfInt & other);
        InfInt operator/(const InfInt & other);
        InfInt operator%(const InfInt & other);
        InfInt operator++();
        InfInt operator++(int);
        InfInt operator--();
        InfInt operator--(int);
        bool operator==(const InfInt & other);
        bool operator!=(const InfInt & other);
        bool operator>(const InfInt & other);
        bool operator<(const InfInt & other);
        bool operator>=(const InfInt & other);
        bool operator<=(const InfInt & other);

        //Bitwise operators
        InfInt operator~();
        InfInt operator&(const InfInt & other);
        InfInt operator|(const InfInt & other);
        InfInt operator<<(const InfInt & other);
        InfInt operator<<(int other);
        InfInt operator>>(const InfInt & other);
        InfInt operator^(const InfInt & other);

        //Assignment operators
        InfInt operator+=(const InfInt & other);
        InfInt operator-=(const InfInt & other);
        InfInt operator*=(const InfInt & other);
        InfInt operator/=(const InfInt & other);
        InfInt operator%=(const InfInt & other);

        //Bitwise assignment operators
        InfInt operator&=(const InfInt & other);
        InfInt operator|=(const InfInt & other);
        InfInt operator^=(const InfInt & other);
        InfInt operator<<=(const InfInt & other);
        InfInt operator>>=(const InfInt & other);

        //Output, Input operators
        operator int();
        friend ostream &operator<<( ostream &output, InfInt &other );
        friend istream &operator>>( istream  &input, InfInt &other );

        //Compare number
        int calcBiggerAbs(InfInt num1, InfInt num2);
        int calcBigger(InfInt num1, InfInt num2);

        //Add
        InfInt absPlus(InfInt n1, InfInt n2);
        string absPlus(string s1, string s2);

        //Subtract
        InfInt absMinus(InfInt n1, InfInt n2);
        string absMinus(string s1, string s2);

        //Multiply
        InfInt absMultiply(InfInt n1, InfInt n2);
        string absMultiply(string s1, string s2);

        //Divide
        InfInt absDivision(InfInt n1, InfInt n2);
        string absDivision(string d, string divisor);

        //Modulu
        InfInt absMod(InfInt n1, InfInt n2);
        string absMod(string d, string divisor);

        //Power
        InfInt absPow(InfInt n, InfInt p);
        string absPow(string s, long long int p);

        //AND
        InfInt AND(InfInt n1, InfInt n2);

        //OR
        InfInt OR(InfInt n1, InfInt n2);

        //XOR
        InfInt XOR(InfInt n1, InfInt n2);

        //Shift Right
        InfInt shiftRight(InfInt n1, InfInt n2);
        string shiftRight(string s1, string s2);

        //Shift Left
        long long int absPow(long long int n, long long int p);

        //Other functions
        string divideStringTo2(string n);
        static string reverseString(string s);
        static void fillWithZeros(string* s, long long int n);
        long int charLength(char* c);
    };

#endif //EX1_FINAL_LARGEINTEGERS_H