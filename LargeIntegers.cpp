#include <iostream>
#include <string.h>
#include "LargeIntegers.h"

enum { pos = 1, neg = 0 };
using namespace std;

    //Default constructor.
    InfInt::InfInt() {
        this->_number    = '0';
        this->_binNumber = '0';
        this->_sign      = pos;
        this->_length    = 0;
    }


    //long int constructor;
    InfInt::InfInt(long int num) {
        bool sign;
        if(num < 0) {
            num *= (-1);
            sign = neg;
        }
        this->_number    = toString(num);
        this->_binNumber = convertDecToBin(this->_number);
        this->_sign      = sign;
        this->_length    = getLength(num);
    }


    //String constructor.
    InfInt::InfInt(string num) {
        if(num.length() > 1) {
            num.erase(0, num.find_first_not_of('0'));
        }
        if(getStrSign(num) == neg) {
            string copy = num;
            this->_number = copy.substr(1, num.length());
            this->_length = num.length() - 1;
        }
        else {
            this->_number    = num;
            this->_length    = num.length();
        }
        this->_binNumber = convertDecToBin(this->_number);
        this->_sign      = (num[0] != '-');
    }


    //String constructor.
    InfInt::InfInt(char* c)  {
        if(c[0] == '-') {
            this->_sign = neg;
            this->_number = c + 1;
        } else {
            this->_sign = pos;
            this->_number = c;
        }
        this->_binNumber = convertDecToBin(c);
        this->_length = charLength(c);
    }


    //Copy constructor.
    InfInt::InfInt(const InfInt &i) {
        this->_number       = i._number;
        this->_binNumber    = i._binNumber;
        this->_sign         = i._sign;
        this->_length       = i._length;
    }


    /********************
    * Function name:           setNumber
    * The inputs:              string newNum
    * The output:              null
    * The function operation:  sets to InfInt a new number.
    ********************/
    void InfInt::setNumber(string newNum) {
        InfInt temp(newNum);
        this->_number    = temp.getNumber();
        this->_binNumber = convertDecToBin(_number);
        this->_sign      = temp._sign;
        this->_length    = temp._length;
    }


    /********************
    * Function name:           setSign
    * The inputs:              bool sign
    * The output:              null
    * The function operation:  sets to InfInt a new sign.
    ********************/
    void InfInt::setSign(bool sign) {
        this->_sign == sign;
    }


    /********************
    * Function name:           getSign
    * The inputs:              null
    * The output:              bool this.sign
    * The function operation:  returns the InfInt's sign.
    ********************/
    bool InfInt::getSign() {
        return this->_sign;
    }


    /********************
    * Function name:           getSign
    * The inputs:              null
    * The output:              bool this.sign
    * The function operation:  returns the InfInt's sign.
    ********************/
    unsigned long long InfInt::getLength() {
        return this->_length;
    }


    /********************
    * Function name:           getNumber
    * The inputs:              null
    * The output:              string this.number
    * The function operation:  returns the InfInt's absolute decimal number.
    ********************/
    string InfInt::getNumber() {
        if(this->_number == "") {
            return this->_number = "0";
        }
        return this->_number;
    }


    /********************
    * Function name:           convertDecToBin
    * The inputs:              string n
    * The output:              string binNum
    * The function operation:  Converts a string represnting a decimal number
    *                         into a binary string.
    ********************/
    string InfInt::convertDecToBin(string n) {
        string binNum   = "";
        int remainder   = 0;
        int i           = 0;
        while(n != "") {
            remainder = (n[n.length() - 1] % 2) + 48;
            binNum.append(1, remainder);
            n = divideStringTo2(n);
            i++;
        }
        //If the result is '0' we return a '0' string.
        if(binNum == "") {
            return "0";
        }
        return reverseString(binNum);
    }


    /********************
    * Function name:           convertBinToDec
    * The inputs:              string b
    * The output:              string dec
    * The function operation:  Converts a binary string into decimal string.
    ********************/
    string InfInt::convertBinToDec(string b) {
        string dec = "";
        for(long long int i = 0; i < b.length(); i++) {
            if(b.at(i) == '1') {
                dec = absPlus(dec, absPow("2", b.length() - i - 1));
            }
        }
        return dec;
    }


    /********************
    * Function name:           operator+
    * The inputs:              const InfInt & other
    * The output:              InfInt sum
    * The function operation:  sum 2 InfInts.
    ********************/
    InfInt InfInt::operator+(const InfInt & other) {
        string s = "";
        //We check what operation we should do (+/-) and the right sign.
        if(this->_sign == pos && other._sign == pos) {
            s = absPlus(*this, other).getNumber();
        }
        else if(this->_sign == neg && other._sign == neg) {
            s = absPlus(*this, other).getNumber();
            s.insert(0, "-");
        }
        else if(this->_sign == pos && other._sign == neg) {
            if(calcBiggerAbs(*this, other) == 1) {
                s = absMinus(other, *this).getNumber();
                s.insert(0, "-");
            } else {
                s = absMinus(*this, other).getNumber();
            }
        }
        else if(this->_sign == neg && other._sign == pos) {
            if(calcBiggerAbs(*this, other) == -1) {
                s = absMinus(*this, other).getNumber();
                s.insert(0, "-");
            } else {
                s = absMinus(other, *this).getNumber();
            }
        }
        return InfInt(s);
    }


    /********************
    * Function name:           operator-
    * The inputs:              const InfInt & other
    * The output:              InfInt difference
    * The function operation:  subtraction of 2 InfInts.
    ********************/
    InfInt InfInt::operator-(const InfInt & other) {
        string s = "";
        //We check what operation we should do (+/-) and the right sign.
        if(this->_sign == pos && other._sign == pos) {
            if(calcBiggerAbs(*this, other) == -1) {
                s = absMinus(*this, other).getNumber();
            } else {
                s = absMinus(other, *this).getNumber();
                s.insert(0, "-");
            }
        }
        else if(this->_sign == neg && other._sign == neg) {
            if(calcBiggerAbs(*this, other) == 1) {
                s = absMinus(other, *this).getNumber();
            } else {
                s = absMinus(*this, other).getNumber();
                s.insert(0, "-");
            }
        }
        else if(this->_sign == pos && other._sign == neg) {
            s = absPlus(*this, other).getNumber();
        } else {
            s = absPlus(*this, other).getNumber();
            s.insert(0, "-");
        }
        //If the result is '-0' we return '0'.
        if(s == "-0") {
            s = "0";
        }
        return InfInt(s);
    }


    /********************
    * Function name:           operator*
    * The inputs:              const InfInt & other
    * The output:              InfInt product
    * The function operation:  multiplication of 2 InfInts.
    ********************/
    InfInt InfInt::operator*(const InfInt & other) {
        string str = absMultiply(*this, other).getNumber();
        //We check what the right sign is.
        if(this->_sign != other._sign) {
            str.insert(0, "-");
        }
        //If the result is '-0' we return '0'.
        if(str == "-0") {
            str = "0";
        }
        return InfInt(str);
    }


    /********************
    * Function name:           operator/
    * The inputs:              const InfInt & other
    * The output:              InfInt quotient
    * The function operation:  division of 2 InfInts.
    ********************/
    InfInt InfInt::operator/(const InfInt & other) {
        string str = absDivision(*this, other).getNumber();
        //We check what the right sign is.
        if(this->_sign != other._sign) {
            str.insert(0, "-");
        }
        //If the result is '-0' we return '0'.
        if(str == "-0") {
            str = "0";
        }
        return InfInt(str);
    }


    /********************
    * Function name:           operator%
    * The inputs:              const InfInt & other
    * The output:              InfInt modulu
    * The function operation:  calculates modulu of 2 InfInts.
    ********************/
    InfInt InfInt::operator%(const InfInt & other) {
        string str = absMod(*this, other).getNumber();
        //We check what the right sign is.
        if(this->_sign != other._sign) {
            str.insert(0, "-");
        }
        //If the result is '-0' we return '0'.
        if(str == "-0") {
            str = "0";
        }
        return InfInt(str);
    }


    /********************
    * Function name:           ++operator
    * The inputs:              null
    * The output:              InfInt temp.
    * The function operation:  calculates ++this.number.
    ********************/
    InfInt InfInt::operator++() {
        //We save a temp InfInt of the original value to be returned.
        InfInt temp = *this;
        setNumber((*this + InfInt("1")).getNumber());
        return temp;
    }


    /********************
    * Function name:           operator++
    * The inputs:              null
    * The output:              InfInt + 1
    * The function operation:  calculates this.number++.
    ********************/
    InfInt InfInt::operator++(int) {
        setNumber((*this + InfInt("1")).getNumber());
        return *this;
    }


    /********************
    * Function name:           --operator
    * The inputs:              null
    * The output:              InfInt temp.
    * The function operation:  calculates --this.number.
    ********************/
    InfInt InfInt::operator--() {
        //We save a temp InfInt of the original value to be returned.
        InfInt temp = *this;
        setNumber((*this - InfInt("1")).getNumber());
        return temp;
    }


    /********************
    * Function name:           --operator
    * The inputs:              null
    * The output:              InfInt temp.
    * The function operation:  calculates --this.number.
    ********************/
    InfInt InfInt::operator--(int) {
        setNumber((*this - InfInt("1")).getNumber());
        return *this;
    }

    /********************
    * Function name:           operator==
    * The inputs:              null
    * The output:              InfInt temp.
    * The function operation:  calculates --this.number.
    ********************/
    bool InfInt::operator==(const InfInt & other) {
        if(calcBigger(*this, other) == 0) {
            return 1;
        } else {
            return 0;
        }
    }


    /********************
    * Function name:           operator!=
    * The inputs:              const InfInt & other
    * The output:              bool equal.
    * The function operation:  Checks if two InfInts are not equal.
    ********************/
    bool InfInt::operator!=(const InfInt & other) {
        if(calcBigger(*this, other) == 0) {
            return 0;
        } else {
            return 1;
        }
    }


    /********************
    * Function name:           operator>
    * The inputs:              const InfInt & other
    * The output:              bool bigger.
    * The function operation:  Checks if this InfInt is bigger than the InfInt on the right hand.
    ********************/
    bool InfInt::operator>(const InfInt & other) {
        if(calcBigger(*this, other) == -1) {
            return 1;
        } else {
            return 0;
        }
    }


    /********************
    * Function name:           operator<
    * The inputs:              const InfInt & other
    * The output:              bool smaller.
    * The function operation:  Checks if this InfInt is smaller than the InfInt on the right hand.
    ********************/
    bool InfInt::operator<(const InfInt & other) {
        if(calcBigger(*this, other) == 1) {
            return 1;
        } else {
            return 0;
        }
    }


    /********************
    * Function name:           operator>=
    * The inputs:              const InfInt & other
    * The output:              bool bigger or equal.
    * The function operation:  Checks if this InfInt is bigger or equal than the InfInt on the right hand.
    ********************/
    bool InfInt::operator>=(const InfInt & other) {
        if((calcBiggerAbs(*this, other) == -1) ||
           (calcBigger(*this, other) == 0))  {
            return 1;
        } else {
            return 0;
        }
    }


    /********************
    * Function name:           operator<=
    * The inputs:              const InfInt & other
    * The output:              bool smaller or equal.
    * The function operation:  Checks if this InfInt is smaller or equal than the InfInt on the right hand.
    ********************/
    bool InfInt::operator<=(const InfInt & other) {
        if((calcBiggerAbs(*this, other) == 1) ||
           (calcBigger(*this, other) == 0))  {
            return 1;
        } else {
            return 0;
        }
    }


    /********************
    * Function name:           operator~
    * The inputs:              null
    * The output:              bitwise NOT of this InfInt.
    * The function operation:  The function changes all of the bits in a binary string to the opposite.
    ********************/
    InfInt InfInt::operator~() {
        string str = "";
        for(long long i = 0; i < _binNumber.length(); i++) {
            if(this->_binNumber.at(i) == '1') {
                str.append(1, '0');
            } else {
                str.append(1, '1');
            }
        }
        str = convertBinToDec(str);
        return InfInt(str);
    }


    /********************
    * Function name:           operator&
    * The inputs:              const InfInt & other
    * The output:              bitwise AND of this InfInt and other InfInt.
    * The function operation:  The function checks for AND of two InfInts.
    ********************/
    InfInt InfInt::operator&(const InfInt & other) {
        string str = AND(*this, other).getNumber();
        return InfInt(str);
    }


    /********************
    * Function name:           operator|
    * The inputs:              const InfInt & other
    * The output:              bitwise OR of this InfInt and other InfInt.
    * The function operation:  The function checks for OR of two InfInts.
    ********************/
    InfInt InfInt::operator|(const InfInt & other) {
        string str = OR(*this, other).getNumber();
        return InfInt(str);
    }


    /********************
    * Function name:           operator<<
    * The inputs:              const InfInt & other
    * The output:              bitwise SHIFT TO LEFT of this InfInt by other.
    * The function operation:  The function multiply the value of this by 2^other.
    ********************/
    InfInt InfInt::operator<<(const InfInt & other) {
        return *this * InfInt(absPow(2, other).getNumber());
    }



    /********************
    * Function name:           operator<<
    * The inputs:              const InfInt & other
    * The output:              bitwise SHIFT TO LEFT of this InfInt by other.
    * The function operation:  The function multiply the value of this by 2^other.
    ********************/
    InfInt InfInt::operator<<(int other) {
        InfInt((long int) other);
        return *this * InfInt(absPow(2, other)).getNumber();
    }


    /********************
    * Function name:           operator>>
    * The inputs:              const InfInt & other
    * The output:              bitwise SHIFT TO RIGHT of this InfInt by other.
    * The function operation:  The function divide this by 2^other.
    ********************/
    InfInt InfInt::operator>>(const InfInt & other) {
        string result = shiftRight(*this, other).getNumber();
        if(result == "") {
            return InfInt("0");
        }
        return InfInt(result);
    }


    /********************
    * Function name:           operator^
    * The inputs:              const InfInt & other
    * The output:              bitwise XOR of this InfInt and InfInt other.
    * The function operation:  The function checks for XOR of two InfInts.
    ********************/
    InfInt InfInt::operator^(const InfInt & other) {
        string str = XOR(*this, other).getNumber();
        return InfInt(str);
    }


    /********************
    * Function name:           operator+=
    * The inputs:              const InfInt & other
    * The output:              this = this + other.
    * The function operation:  The function assign this + other into this.
    ********************/
    InfInt InfInt::operator+=(const InfInt & other) {
        setNumber((*this + other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator-=
    * The inputs:              const InfInt & other
    * The output:              this = this - other.
    * The function operation:  The function assign this - other into this.
    ********************/
    InfInt InfInt::operator-=(const InfInt & other) {
        setNumber((*this - other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator*=
    * The inputs:              const InfInt & other
    * The output:              this = this * other.
    * The function operation:  The function assign this * other into this.
    ********************/
    InfInt InfInt::operator*=(const InfInt & other) {
        setNumber((*this * other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator/=
    * The inputs:              const InfInt & other
    * The output:              this = this / other.
    * The function operation:  The function assign this / other into this.
    ********************/
    InfInt InfInt::operator/=(const InfInt & other) {
        setNumber((*this / other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator%=
    * The inputs:              const InfInt & other
    * The output:              this = this % other.
    * The function operation:  The function assign this % other into this.
    ********************/
    InfInt InfInt::operator%=(const InfInt & other) {
        setNumber((*this % other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator&=
    * The inputs:              const InfInt & other
    * The output:              this = this & other.
    * The function operation:  The function assign this & other into this.
    ********************/
    InfInt InfInt::operator&=(const InfInt & other) {
        setNumber((*this & other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator|=
    * The inputs:              const InfInt & other
    * The output:              this = this | other.
    * The function operation:  The function assign this | other into this.
    ********************/
    InfInt InfInt::operator|=(const InfInt & other) {
        setNumber((*this | other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator^=
    * The inputs:              const InfInt & other
    * The output:              this = this ^ other.
    * The function operation:  The function assign this ^ other into this.
    ********************/
    InfInt InfInt::operator^=(const InfInt & other) {
        setNumber((*this ^ other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator<<=
    * The inputs:              const InfInt & other
    * The output:              this = this << other.
    * The function operation:  The function assign this << other into this.
    ********************/
    InfInt InfInt::operator<<=(const InfInt & other) {
        setNumber((*this << other).getNumber());
        return *this;
    }

    /********************
    * Function name:           operator>>=
    * The inputs:              const InfInt & other
    * The output:              this = this >> other.
    * The function operation:  The function assign this >> other into this.
    ********************/
    InfInt InfInt::operator>>=(const InfInt & other) {
        setNumber((*this >> other).getNumber());
        return *this;
    }


    /********************
    * Function name:           operator(int)
    * The inputs:              null
    * The output:              this integer value.
    * The function operation:  The function assign other into this.
    ********************/
    InfInt::operator int() {
        return (int) toLongInt(this->_number);
    }


    /********************
    * Function name:           ostream &operator<<
    * The inputs:              ostream &output, InfInt &other
    * The output:              output.
    * The function operation:  The function streams other into output.
    ********************/
    ostream &operator<<( ostream &output, InfInt &other ) {
        if(other._sign == neg) {
            output << "-";
        }
        output << other.getNumber();
        return output;
    }


    /********************
    * Function name:           friend istream &operator>>
    * The inputs:              ostream &input, InfInt &other
    * The output:              input.
    * The function operation:  The function streams other into input.
    ********************/
    istream &operator>>( istream  &input, InfInt &other ) {
        string s = "";
        input >> s;
        other.setNumber(s);
        return input;
    }


    /********************
    * Function name:           toString
    * The inputs:              long int num
    * The output:              string strNum.
    * The function operation:  The function converts a string to a long int.
    ********************/
    string InfInt::toString(long int num) {
        if(num == 0) {
            return "0";
        }
        int tmpNum  = num;
        int numSize = 0;
        //Counting the numbers size;
        while(tmpNum != 0) {
            numSize++;
            tmpNum /= 10;
        }
        //Copying the number to a string.
        if(num > 0) {
            string strNum = "";
            for(int i = numSize - 1; i >= 0; i--) {
                int d       = num % 10;
                strNum.append(1, d + 48);
                num         /= 10;
            }
            return strNum;
            //If the number is negative we add '-'.
        } else {
            string strNum = "-";
            for(int i = numSize; i > 0; i--) {
                int d       = -1 * num % 10;
                strNum.append(1, d + 48);
                num         /= 10;
            }
            return strNum;
        }
    }


    /********************
    * Function name:           toLongInt
    * The inputs:              string s
    * The output:              string sum.
    * The function operation:  The function converts a long int to a string.
    ********************/
    long int InfInt::toLongInt(string s) {
        long int sum = 0;
        if(s.at(0) == '-') {
            for (long int i = 1; i < s.length(); i++) {
                sum = sum + (absPow(10, s.length() - 1 - i) * ((long long int) s.at(i) - 48));
            }
            sum *= -1;
        } else {
            for (long int i = 0; i < s.length(); i++) {
                sum = sum + (absPow(10, s.length() - 1 - i) * ((long long int) s.at(i) - 48));
            }
        }
        return sum;
    }


    /********************
    * Function name:           getStrSign
    * The inputs:              string n.
    * The output:              the sign.
    * The function operation:  The function returns a string's sign.
    ********************/
    bool InfInt::getStrSign(string n) {
        if (n[0] == '-') {
            return neg;
        } else {
            return pos;
        }
    }


    /********************
    * Function name:           getLength
    * The inputs:              long int n.
    * The output:              long long int c.
    * The function operation:  The function returns number of digits in long int.
    ********************/
    unsigned long long int InfInt::getLength(long int n) {
        unsigned long long int c = 0;
        while(n != 0) {
            c++;
            n /= 10;
        }
        return c;
    }


    /********************
    * Function name:           divideStringTo2
    * The inputs:              string n.
    * The output:              string n/2.
    * The function operation:  The function divide a string by 2.
    ********************/
    string InfInt::divideStringTo2(string n) {
        int nextAdd = 0;
        for(int i = 0; i < n.length(); i++) {
            char currentDigit = n[i];
            int add = nextAdd;
            if((currentDigit - 48) % 2 != 0) {
                nextAdd = 5;
            } else {
                nextAdd = 0;
            }
            n[i] = ((currentDigit - 48) / 2) + 48 + add;
        }
        if(n[0] == '0' && n.length() > 0) {
            n = n.substr(1, n.length());
        }
        return n;
    }


    /********************
    * Function name:           reverseString
    * The inputs:              string s.
    * The output:              reversed string.
    * The function operation:  The function reverse a string.
    ********************/
    string InfInt::reverseString(string s) {
        int x = s.length();
        for(int i = 0; i < s.length() / 2; i++) {
            swap(s[i], s[s.length() - i - 1]);
        }
        return s;
    }


    /********************
    * Function name:           fillWithZeros
    * The inputs:              string* s, long long int n.
    * The output:              s with filled n of zeros at the beggining.
    * The function operation:  The function adds zeros to the beggining of s.
    ********************/
    void InfInt::fillWithZeros(string* s, long long int n) {
        for(int i = 0; i < n; i++) {
            s->insert(0, "0");
        }
    }


    /********************
    * Function name:           calcBiggerAbs
    * The inputs:              InfInt num1, InfInt num2.
    * The output:              1 if right argument is bigger, -1 if left argument is bigger, 0 if arguments are equal.
    * The function operation:  checks which (abs)number is bigger.
    ********************/
    int InfInt::calcBiggerAbs(InfInt num1, InfInt num2) {
        if (num1.getLength() > num2.getLength()) {
            return -1;
        }
        else if (num1.getLength() < num2.getLength()) {
            return 1;
        }
        else {
            for (int i = 0; i < num1.getLength(); i++) {
                if (num1._number[i] > num2._number[i]) {
                    return -1;
                }
                else if (num1._number[i] < num2._number[i]) {
                    return 1;
                }
            }
            //In case both numbers are equals.
            return 0;
        }
    }


    /********************
    * Function name:           calcBigger
    * The inputs:              InfInt num1, InfInt num2.
    * The output:              1 if right argument is bigger, -1 if left argument is bigger, 0 if arguments are equal.
    * The function operation:  checks which number is bigger.
    ********************/
    int InfInt::calcBigger(InfInt num1, InfInt num2) {
        if(num1._sign == pos && num2._sign == pos) {
            return calcBiggerAbs(num1, num2);
        }
        else if((num1._sign == neg && num2._sign == neg)) {
            return (-1) * calcBiggerAbs(num1, num2);
        }
        else if(num1._sign == pos && num2._sign == neg) {
            return -1;
        }
        else return 0;
    }


    /********************
    * Function name:           absPlus
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the sum of 2 absolute numbers.
    * The function operation:  the function converts 2 strings and send them to absPlus function.
    ********************/
    InfInt InfInt::absPlus(InfInt n1, InfInt n2) {
        string result = absPlus(n1.getNumber(), n2.getNumber());
        return InfInt(result);
    }


    /********************
    * Function name:           absPlus
    * The inputs:              string s1, string s2.
    * The output:              the string sum of 2 absolute numbers.
    * The function operation:  the function adds two strings.
    ********************/
    string InfInt::absPlus(string s1, string s2) {
        string longStr;
        string shortStr;
        string newStr;
        long long int longStrLength = 0;
        long long int shortStrLength = 0;
        //We make sure both number are assigned to the right variables.
        if(s1.length() >= s2.length()) {
            longStr         = s1;
            longStrLength   = s1.length();
            shortStr        = s2;
            shortStrLength  = s2.length();
        }
        else if(s1.length() < s2.length()) {
            shortStr        = s1;;
            shortStrLength  = s1.length();
            longStr         = s2;;
            longStrLength   = s2.length();
        }
        long long int difference = longStrLength - shortStrLength;
        //We make sure both nubmers are in the same length.
        fillWithZeros(&shortStr, difference + 1);
        fillWithZeros(&longStr, 1);
        //Simple sum algorithem.
        int remainder = 0;
        for(int i = 0; i < longStr.length(); i++) {
            char digit = (((longStr[longStrLength - i] - 48) + (shortStr[longStrLength - i] - 48) + remainder) % 10) ;
            int d = ((longStr[longStrLength - i] - 48) + (shortStr[longStrLength - i] - 48)) % 10;
            newStr.append(1, (digit + 48));
            if((longStr[longStrLength - i] - 48) + (shortStr[longStrLength - i] - 48) + remainder >= 10) {
                remainder = 1;
            } else {
                remainder = 0;
            }
        }
        newStr = reverseString(newStr);
        newStr.erase(0, newStr.find_first_not_of('0'));
        //If after all zeros were erased we get "" we return "0".
        if(newStr == "") {
            newStr = "0";
        }
        return newStr;
    }


    /********************
    * Function name:           absMinus
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the difference of 2 absolute numbers.
    * The function operation:  the function converts 2 strings and send them to absMinus function.
    ********************/
    InfInt InfInt::absMinus(InfInt n1, InfInt n2) {
        string result = absMinus(n1.getNumber(), n2.getNumber());
        return InfInt(result);
    }


    /********************
    * Function name:           absPlus
    * The inputs:              string s1, string s2.
    * The output:              the string sum of 2 absolute numbers.
    * The function operation:  the function substract two strings.
    ********************/
    string InfInt::absMinus(string s1, string s2) {
        string longStr;
        string shortStr;
        string newStr = "";
        long long int longStrLength = 0;
        long long int shortStrLength = 0;
        //We make sure both number are assigned to the right variables.
        if (s1.length() >= s2.length()) {
            longStr         = s1;
            longStrLength   = s1.length();
            shortStr        = s2;
            shortStrLength  = s2.length();
        } else if (s1.length() < s2.length()) {
            shortStr        = s1;
            shortStrLength  = s1.length();
            longStr         = s2;
            longStrLength   = s2.length();
        }
        long long int difference = longStrLength - shortStrLength;
        fillWithZeros(&shortStr, difference + 1);
        fillWithZeros(&longStr, 1);
        // Reverse both of strings
        longStr = reverseString(longStr);
        shortStr = reverseString(shortStr);
        int carry = 0;
        for (long long int i = 0; i < shortStrLength; i++) {
            int sub = ((longStr[i]- 48) - (shortStr[i]- 48) - carry);
            if (sub < 0)
            {
                sub += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            newStr.push_back(sub + '0');
        }
        for (long long int  i = shortStrLength; i < longStrLength; i++) {
            int sub = ((longStr[i] - 48) - carry);
            // if the sub value is -ve, then make it positive
            if (sub < 0) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            newStr.push_back(sub + '0');
        }
        return reverseString(newStr);
    }


    /********************
    * Function name:           absMultiply
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result of multiplied of 2 absolute numbers.
    * The function operation:  the function converts 2 strings and send them to absMultiply function.
    ********************/
    InfInt InfInt::absMultiply(InfInt n1, InfInt n2){
        string result = absMultiply(n1.getNumber(), n2.getNumber());
        return InfInt(result);
    }


    /********************
    * Function name:           absMultiply
    * The inputs:              string s1, string s2.
    * The output:              the string result of 2 absolute numbers multiplied.
    * The function operation:  the function multiply two strings.
    ********************/
    string InfInt::absMultiply(string s1, string s2) {
        int n = s1.length() + s2.length();
        int i, j, product, carry;
        string q = "";
        for (i = s1.length() - 1; i >= 0; i--) {
            carry = 0;
            for (j = s2.length() - 1; j >= 0; j--) {
                product = carry + q[i + j + 1] + (s1[i] - '0') * (s2[j] - '0');
                q[i + j + 1] = product % 10;
                carry = product / 10;
            }
            q[i + j + 1] = carry;
        }
        string rst = "";
        i = 0;
        while (i < n - 1 && q[i] == 0) {
            i++;
        }
        while (i < n) {
            rst += (q[i++] + '0');
        }
        return rst;
    }


    /********************
    * Function name:           absDivision
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result of division of 2 absolute numbers.
    * The function operation:  the function converts 2 strings and send them to absDivision function.
    ********************/
    InfInt InfInt::absDivision(InfInt n1, InfInt n2) {
        string result = absDivision(n1.getNumber(), n2.getNumber());
        return InfInt(result);
    }


    /********************
    * Function name:           absDivision
    * The inputs:              string s1, string s2.
    * The output:              the string result of 2 absolute numbers divided.
    * The function operation:  the function divide two strings using bit shifting.
    ********************/
    string InfInt::absDivision(string d, string divisor) {
        InfInt dividend(d);
        InfInt quotient("0");
        int nPos = -1;
        InfInt tempDivisor(divisor);
        while (tempDivisor <= d) {
            tempDivisor = tempDivisor << InfInt("1");
            nPos++;
        }
        tempDivisor = tempDivisor >> InfInt("1");
        while (nPos > -1) {
            if (dividend >= tempDivisor) {
                quotient = quotient + (InfInt("1") << InfInt(nPos));
                dividend = dividend - tempDivisor;
            }
            tempDivisor = tempDivisor >> InfInt("1");
            nPos -= 1;
        }
        return quotient.getNumber();
    }


    /********************
    * Function name:           absMod
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result of modulu of 2 absolute numbers.
    * The function operation:  the function converts 2 strings and send them to absMod function.
    ********************/
    InfInt InfInt::absMod(InfInt n1, InfInt n2) {
        string result = absMod(n1.getNumber(), n2.getNumber());
        return InfInt(result);
    }


    /********************
    * Function name:           absDivision
    * The inputs:              string s1, string s2.
    * The output:              the string result of 2 absolute numbers divided.
    * The function operation:  the function divide two strings using bit shifting.
    ********************/
    string InfInt::absMod(string d, string divisor) {
        InfInt dividend(d);
        InfInt quotient("0");
        int nPos = -1;
        InfInt tempDivisor(divisor);
        while (tempDivisor <= d) {
            tempDivisor = tempDivisor << InfInt("1");
            nPos ++;
        }
        tempDivisor = tempDivisor >> InfInt("1");
        while (nPos > -1) {
            if (dividend >= tempDivisor) {
                quotient = quotient + (InfInt("1") << InfInt(nPos));
                dividend = dividend - tempDivisor;
            }
            tempDivisor = tempDivisor >> InfInt("1");
            nPos -= 1;
        }
        return dividend.getNumber();
    }


    /********************
    * Function name:           absPow
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result of power n1^n2.
    * The function operation:  the function converts multipling n1 n2 times.
    ********************/
    InfInt InfInt::absPow(InfInt n, InfInt p) {
        long long int power = toLongInt(p.getNumber());
        string result = absPow(n.getNumber(), power);
        return result;
    }


    /********************
    * Function name:           absPow
    * The inputs:              string s1, string s2.
    * The output:              the result of power n1^n2.
    * The function operation:  the function converts multipling n1 n2 times.
    ********************/
    string InfInt::absPow(string s, long long int p) {
        string n = s;
        if(p == 0) {
            return "1";
        }
        if(p == 1) {
            return s;
        }
        for(long long int i = 0; i < p - 1; i++) {
            s = (InfInt(s) * InfInt(n)).getNumber();
        }
        return s;
    }


    /********************
    * Function name:           AND
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result n1 & n2.
    * The function operation:  the function gets 2 binary string and do the & bitwise operation.
    ********************/
    InfInt InfInt::AND(InfInt n1, InfInt n2) {
        string longStr = n1._binNumber;
        string shortStr = n2._binNumber;
        if(n2._length > n1._length) {
            swap(longStr, shortStr);
        }
        //Make sure both numbers in the same length.
        fillWithZeros(&shortStr, longStr.length() - shortStr.length());
        string newStr = "";
        for(long long int i = 0; i < longStr.length(); i++) {
            if(longStr.at(i) == '1' && shortStr.at(i) == '1') {
                newStr.append(1, '1');
            } else {
                newStr.append(1, '0');
            }
        }
        newStr.erase(0, newStr.find_first_not_of('0'));
        if(newStr == "") {
            return InfInt("0");
        }
        InfInt newInf(convertBinToDec(newStr));
        if(n1._sign == neg && n2._sign == neg) {
            newInf.setSign(neg);
        }
        return InfInt(convertBinToDec(newStr));
    }


    /********************
    * Function name:           OR
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result n1 | n2.
    * The function operation:  the function gets 2 binary string and do the | bitwise operation.
    ********************/
    InfInt InfInt::OR(InfInt n1, InfInt n2) {
        string longStr  = n1._binNumber;
        string shortStr = n2._binNumber;
        if(n2._length > n1._length) {
            swap(longStr, shortStr);
        }
        fillWithZeros(&shortStr, longStr.length() - shortStr.length());
        string newStr = "";
        for(long long int i = 0; i < longStr.length(); i++) {
            if(longStr.at(i) == '1' || shortStr.at(i) == '1') {
                newStr.append(1, '1');
            } else {
                newStr.append(1, '0');
            }
        }
        newStr.erase(0, newStr.find_first_not_of('0'));
        if(newStr == "") {
            return InfInt("0");
        }
        InfInt newInf(convertBinToDec(newStr));
        if(n1._sign == neg || n2._sign == neg) {
            newInf.setSign(neg);
        }
        return InfInt(convertBinToDec(newStr));
    }


    /********************
    * Function name:           XOR
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result n1 ^ n2.
    * The function operation:  the function gets 2 binary string and do the ^ bitwise operation.
    ********************/
    InfInt InfInt::XOR(InfInt n1, InfInt n2) {
        string longStr = n1._binNumber;
        string shortStr = n2._binNumber;
        if(n2._length > n1._length) {
            swap(longStr, shortStr);
        }
        fillWithZeros(&shortStr, longStr.length() - shortStr.length());
        string newStr = "";
        for(long long int i = 0; i < longStr.length(); i++) {
            if((longStr.at(i) == '1' && shortStr.at(i) == '0') ||
               (longStr.at(i) == '0' && shortStr.at(i) == '1')) {
                newStr.append(1, '1');
            } else {
                newStr.append(1, '0');
            }
        }
        newStr.erase(0, newStr.find_first_not_of('0'));
        if(newStr == "") {
            return InfInt("0");
        }
        InfInt newInf(convertBinToDec(newStr));
        if(n1._sign !=  n2._sign) {
            newInf.setSign(neg);
        }
        return InfInt(convertBinToDec(newStr));
    }


    /********************
    * Function name:           shiftRight
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result n1 >> n2.
    * The function operation:  the function shifts n1 by n2 times.
    ********************/
    InfInt InfInt::shiftRight(InfInt n1, InfInt n2) {
        string s1 = n1._binNumber;
        string s2 = n2._number;
        string result = shiftRight(s1, s2);
        return InfInt(result);
    }


    /********************
    * Function name:           shiftRight
    * The inputs:              InfInt n1, InfInt n2.
    * The output:              the result n1 >> n2.
    * The function operation:  the function removing n2 zeros from n1 and add n2 zeros of n1.
    ********************/
    string InfInt::shiftRight(string s1, string s2) {
        long int l = toLongInt(s2);
        if(s2 == "0") {
            return s1;
        }
        string result = s1.erase(s1.length() - l);
        for(long int i = 0; i < l; i++) {
            result.insert(0, "0");
        }
        if(result == "") {
            return "0";
        }
        return convertBinToDec(result);
    }


    /********************
    * Function name:           absPow
    * The inputs:              long long int n, long long int p.
    * The output:              the result n1 >> n2.
    * The function operation:  the function removing n2 zeros from n1 and add n2 zeros of n1.
    ********************/
    long long int InfInt::absPow(long long int n, long long int p) {
        if (p == 0) {
            return 1;
        }
        long long int sum = n;
        for(long long int i = 0; i < p - 1; i++) {
            sum = sum * n;
        }
        return sum;
    }


    /********************
    * Function name:           charLength
    * The inputs:              char* c
    * The output:              long int i.
    * The function operation:  calculates length of char*.
    ********************/
    long int charLength(char* c) {
        long int i = 0;
        while(c[i] != '\0') {
            i++;
        }
        return i;
    }