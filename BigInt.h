/*
 * Big Integer implementation in C++
 * Author: Murali K                                 
 * Date: 27 March 2013
 */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
#include<iostream>
#include<ostream>

#include<vector>
#include<algorithm>
#include<string>
#include<cassert>


class BigInt {
private: std::vector<char> num;

public:
    BigInt(std::string number);
    BigInt(int num);
    BigInt();
    BigInt trim();
    std::string toString();
    void printVector();
    BigInt add(BigInt b);
    BigInt tens_complement();
    void normalize(BigInt &b);
    BigInt subtract(BigInt b);
    BigInt multiply(BigInt& b);
    BigInt multiply(int b);
    int max(int a, int b);
    BigInt factorial(int num);

    /*operators for big int */
    BigInt operator+(BigInt& b);
    BigInt operator-(BigInt& b);
    BigInt operator*(BigInt& b);
};

BigInt::BigInt() {

}

BigInt::BigInt(int n) {
    while(n) {
        this->num.push_back(n%10);
        n = n/10;
    }
    this->num.push_back(0);
    /* decide the sign bit of the number 1=negative 0=positive*/
    if(n<0) this->num.push_back(1);
    else this->num.push_back(0);
}

BigInt::BigInt(std::string number) {
    bool error_flag = false;
    int i;
    if(number.size() == 0) {
        std::cout<<"\nInvalid number\n";
        /* insert zero when error */
        this->num.push_back(0);
        this->num.push_back(0);
    }
    /* insert digit by digit in reverse order into vector till end except the last character(i=0; possibly sign)*/
    for(i=(int)number.size()-1; i>0; i--) {
        if(number[i]-'0' >=0 && number[i]-'0'<=9)
            this->num.push_back(number[i]-'0');   
        else {
            error_flag = true;
            break;
        }
    }
    /*decide sign bit*/
    if(i==0) {
        if(number[i]=='-') {
            this->num.push_back(1);
        }
        else if(number[i] == '+') {
            this->num.push_back(0);
        }
        else {
            /* if sign is not passed then insert the number and set positive bit */
            if(number[i]-'0' >=0 && number[i]-'0'<=9) {
                this->num.push_back(number[i]-'0');   
                this->num.push_back(0);   
            }
            else {
                error_flag = true;
            }
        }
    }
    
    /* fix */
    int bit = this->num[this->num.size()-1];
    this->num.pop_back();
    this->num.push_back(0);
    this->num.push_back(bit);

    if(this->num.size() <= 1) {
        std::cout<<"only sign is being passed!!\n";
        exit(10);
    }
    if(error_flag) std::cout<<"\nFATAL ERROR\n";
}

BigInt BigInt::trim() {
    /* if only 2 elements then a zero at end will just mean its a positive number. so nothing to trim */
    while(this->num.size()>2 && this->num[this->num.size()-1] == 0 && this->num[this->num.size()-2] == 0) this->num.pop_back();
    return *this;
}

void BigInt::printVector() {
    for(int i=0; i<this->num.size(); i++) std::cout<<(int)this->num[i];
}

std::string BigInt::toString() {
    int i;
    std::string s;
    for(i=this->num.size()-2; i>=0; i--) {
        s.push_back(this->num[i]+'0');
    }
    if(this->num[this->num.size()-1] == 1) 
        s.insert(0,"-");
    return s;
}

int BigInt::max(int a, int b) {
    if(a>b) return a;
    return b;
}

void BigInt::normalize(BigInt &b) {

    if(this->num.size() > b.num.size()) {
        char msb = b.num[b.num.size()-1];
        for(int i=b.num.size(); i<this->num.size(); i++) b.num.push_back(msb);
    }
    else {
        char msb = this->num[this->num.size()-1];
        for(int i=this->num.size(); i<b.num.size(); i++) this->num.push_back(msb);
    }
}

BigInt BigInt::tens_complement() {
    BigInt comp;
    int carry = 0, i, diff, size_a = this->num.size();
    
    assert(size_a>=2);

    diff = 10 - this->num[0];
    carry = diff/10;
    diff = diff%10;
    comp.num.push_back(diff);

    for(i=1; i<size_a; i++) {
        diff = 9 - this->num[i] + carry;
        carry = diff/10;
        diff = diff % 10;
        comp.num.push_back(diff);
    }
    if(carry) comp.num.push_back(carry);
    return comp;
}

BigInt BigInt::add(BigInt b) {
    BigInt a = (*this), s;
    char sum = 0, carry = 0;
    int i, j, size;

    /*check if a or b are negative and complement if so */
    if(a.num[a.num.size()-1] == 1) {
        a.num[a.num.size()-1] = 0;
        a = a.tens_complement();
        a.num.push_back(9);
    }
    if(b.num[b.num.size()-1] == 1) {
        b.num[b.num.size()-1] = 0;
        b = b.tens_complement();
        b.num.push_back(9);
    }

    /*normalize size and update*/
    if(a.num.size() != b.num.size() && (a.num[a.num.size()-1] == 9 || b.num[b.num.size()-1] == 9)) {
        a.normalize(b);
    }

    /* add element by element ignoring the sign bit */
    for(i=0, j=0; i<b.num.size() && j<a.num.size(); i++, j++) {
        sum = b.num[i] + a.num[j] + carry;
        carry = sum/10;
        sum = sum%10;
        s.num.push_back(sum);
    }
    while(i<b.num.size()) {
        sum = b.num[i] + carry;
        carry = sum/10;
        sum = sum%10;
        s.num.push_back(sum);
        i++;
    }
    while(j<a.num.size()) {
        sum = a.num[j] + carry;
        carry = sum/10;
        sum = sum%10;
        s.num.push_back(sum);
        j++;
    }
    if(carry) s.num.push_back(carry);

    /* decide the sign bit based on various cases */
    size = s.num.size();
    /*when result has same size as the max of numbers getting added */
    if(size == max(a.num.size(), b.num.size())) {
        if(s.num[size-1] == 0 ) return s.trim();
        else if(s.num[size-1] == 9) {
            s = s.tens_complement();
            s = s.trim();
            s.num[s.num.size()-1] = 1;
        }
        else {
            s.num.push_back(0);
        }
    }
    /*if size of result is greater than the numbers getting added */
    else if(size > max(a.num.size(),b.num.size())){
        if(a.num[a.num.size()-1] == 9 || b.num[b.num.size()-1] == 9 ) {
            s.num.pop_back();
        }
        else if(a.num[a.num.size()-1] == 0 && b.num[b.num.size()-1] == 0) {
            s.num.push_back(0);
        }
        if(s.num[s.num.size()-1] == 9) {
            s = s.tens_complement();
            s = s.trim();
            s.num[s.num.size()-1] = 1;
        }
    }
    return s.trim();
}

BigInt BigInt::subtract(BigInt b) {
    
    BigInt aa = (*this), bb = b;
    
    if(bb.num[bb.num.size()-1] == 1) {
        /* minus of minus = plus */    
        bb.num[bb.num.size()-1] = 0;
    }
    else {
        bb = bb.tens_complement();
    }

    if(aa.num[aa.num.size()-1] == 1) {
        aa.num[aa.num.size()-1] = 0;
        aa = aa.tens_complement();
    }
    return aa.add(bb);
}

BigInt BigInt::multiply(int b) {
    BigInt c;
    int i, size = 0, pro = 0, carry = 0;

    i = b;
    while(i) {
        size++;
        i = i/10;
    }
    size = size + this->num.size();
    
    for(i=0; i<size; i++) {
        c.num.push_back(0);
    }
    for(i=0; i<this->num.size(); i++) {
        pro = this->num[i] * b + carry;
        carry = pro/10;
        pro = pro%10;
        c.num[i] += pro;
    }
    while(carry) {
        c.num[i++] = carry%10;
        carry = carry/10;
    }
    return c.trim();
}


BigInt BigInt::multiply(BigInt& b) {
    
    BigInt c;
    int j,k, size = this->num.size() + b.num.size();
    for(j=0; j<size; j++) {
        c.num.push_back(0);
    }
    
    char carry = 0, pro = 0;
    for(j=0; j<b.num.size()-1; j++) {
        carry = 0;
        for(k=0; k<this->num.size()-1; k++) {
            pro = b.num[j]*this->num[k];
            pro = pro + c.num[j+k] + carry;
            carry = pro/10;
            pro = pro%10;
            c.num[j+k] = pro;
        }
        c.num[j+k] = carry;
    }
    /*set sign bit*/
    c = c.trim();
    c.num.push_back(this->num[this->num.size()-1] ^ b.num[b.num.size()-1]);
    return c.trim();
}

BigInt BigInt::factorial(int num) {
    BigInt fact("1");
    for(int i=2; i<=num; i++) {
        fact = fact.multiply(i);
    }
    return fact;
}


BigInt BigInt::operator+(BigInt& b) {
    return this->add(b);
}

BigInt BigInt::operator-(BigInt& b) {
    return this->subtract(b);
}

BigInt BigInt::operator*(BigInt& b) {
    return this->multiply(b);
}
