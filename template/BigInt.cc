// -*- coding: utf-8 -*-
// C++ Big integer Class.
// created: 2014-06-27 18:46:37
// Time-stamp: <2014-08-07 20:51:21 scinart>

#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>

#define SSTR( x ) dynamic_cast<std::ostringstream&>((std::ostringstream()<<std::dec<<x)).str()
typedef unsigned char uint_8;
typedef signed char int_8;
void dec_0_(char& c){c-='0';}
void inc_0_(char& c){c+='0';}
bool char_is_not_0(char c){return c;}
using namespace std;
class BigInt
{
private:
    // digits are stored in reversed order.
    string digits;
    int_8 sign;
    const uint_8 base;
public:

    static BigInt ZERO(uint_8 b){return BigInt(char(0),0,b);}
    static BigInt ONE(uint_8 b){return BigInt(char(1),1,b);}

    BigInt():digits(1,char(0)),sign(0),base(10){}
    BigInt(char c, int_8 s, uint_8 b=10):digits(1,c),sign(s),base(b){}
private:
    BigInt(string d, int_8 s, uint_8 b):digits(d),sign(s),base(b){}
public:
    BigInt(int_8 s, string d, uint_8 b=10):digits(d),sign(s),base(b){
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_);
    }
    BigInt(const BigInt& rhs):digits(rhs.digits),sign(rhs.sign),base(rhs.base){}
    BigInt(unsigned u):digits(SSTR(u)),sign(u>0), base(10){//base10 专用
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_);
    }
    BigInt(signed u):base(10) {//base10 专用
        int v=u;if(v<0)v=-v; digits=(SSTR(v));
        if(u>0)sign=1;else sign=(u?-1:0);
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_);
    }

    friend ostream& operator<<(ostream& os, const BigInt& bi)
    { //base10或以下 专用
        string str(bi.digits);
        std::reverse(str.begin(), str.end());
        for_each(str.begin(),str.end(),inc_0_);
        return ((bi.sign<0)?(os<<'-'<<str):(os<<str));
    }
    string to_string()
    {
        //base10或以下 专用
        string str(digits);
        std::reverse(str.begin(), str.end());
        for_each(str.begin(),str.end(),inc_0_);
        return str;
    }

    BigInt& normalize();
    BigInt& take_negative(){sign=-sign; return *this;}
    BigInt& force_negative(){sign=sign?-1:0; return *this;}
    BigInt& force_positive(){sign=sign?1:0; return *this;}
    bool is_positive()const{return sign>0;}
    bool is_negetive()const{return sign<0;}
    bool is_netrual()const{return sign==0;}
    // the following must have the same base.
    BigInt& operator=(const BigInt& rhs){digits=rhs.digits; sign=rhs.sign; return *this;}
    bool abslt(const BigInt& rhs)const
    {
        int this_len = digits.length();
        int rhs_len = rhs.digits.length();
        if(this_len>rhs_len) return false;
        if(this_len<rhs_len) return true;
        for(int i=this_len-1; i>=0; i--)
        {
            if(digits[i]<rhs.digits[i]) return true;
            if(digits[i]>rhs.digits[i]) return false;
        }
        return false;
    }

    BigInt operator+(const BigInt& rhs)const;
    BigInt& operator+=(const BigInt& rhs);
    BigInt operator-()const{return BigInt(digits, -sign, base);};
    BigInt operator-(const BigInt& rhs)const;
    BigInt& operator-=(const BigInt& rhs);
    BigInt operator*(const BigInt& rhs)const;
    BigInt& operator*=(const uint_8& digit);
    BigInt& operator*=(const BigInt& rhs);
    void operator/(const BigInt& rhs, BigInt& ans, BigInt& mod)
    {
        
    }
public:
    BigInt& operator<<=(int bits){if(sign) {string s(bits,char(0)); digits=s+digits;} return *this;}
    BigInt& operator>>=(int bits){if(sign) {digits = digits.substr(bits);} return *this;}
    BigInt operator<<(int bits){return ((BigInt(*this))<<=bits);}
    BigInt operator>>(int bits){return ((BigInt(*this))>>=bits);}
};



BigInt& BigInt::normalize()
{
    digits.erase(std::find_if(digits.rbegin(), digits.rend(), char_is_not_0).base(), digits.end());
    if(digits.length()==0)
    {
        digits=char(0);
        sign=0;
    }
    return *this;
}
BigInt BigInt::operator+(const BigInt& rhs)const
{
    if(digits.length()>=rhs.digits.length())
    {
        return (BigInt(*this)+=rhs);
    }
    else
    {
        return (BigInt(rhs)+=(*this));
    }
}
BigInt& BigInt::operator+=(const BigInt& rhs)
{
    int this_len = digits.length();
    int rhs_len = rhs.digits.length();
    if(this_len>=rhs_len && sign==rhs.sign)
    {
        uint_8 carry = 0;
        int i;
        for(i=0; i<rhs_len; i++)
        {
            uint_8 sum=digits[i]+rhs.digits[i]+carry;
            digits[i] = sum%base;
            carry=(sum>=base);
        }
        while(carry)
        {
            if(i<this_len)
            {
                if(digits[i]==char(base-1))
                {
                    digits[i]=char(0);
                    i++;
                }
                else
                {
                    digits[i]++;
                    carry=0;
                }
            }
            else
            {
                digits+=char(1);
                carry=0;
            }
        }
    }
    else if (sign==rhs.sign)
    {
        *this = (BigInt(rhs)+=(*this));
    }
    else
    {
        if (abslt(rhs))
        {
            (*this) = (BigInt(rhs)+=(*this));
        }
        else
        {
            int_8 carry = 0;
            int i;
            for(i=0; i<rhs_len; i++)
            {
                int_8 sum=base+digits[i]-rhs.digits[i]-carry;
                digits[i] = sum%base;
                carry=((sum>=base)?0:1);
            }
            while(carry)
            {
                if(i<this_len)
                {
                    if(digits[i]==char(0))
                    {
                        digits[i]=char(base-1);
                        i++;
                    }
                    else
                    {
                        digits[i]--;
                        carry=0;
                    }
                }
                else
                {
                    cerr<<" never happen.\n";
                    assert(false);
                }
            }
            this->normalize();
        }
    }
    return *this;
}
BigInt BigInt::operator*(const BigInt& rhs)const
{
    if(digits.length()>=rhs.digits.length())
        return (BigInt(*this)*=rhs);
    else
        return (BigInt(rhs)*=(*this));
}
BigInt& BigInt::operator*=(const uint_8& digit)
{
    if(digit)
    {
        BigInt tmp(*this);
        for(int i=1; i<digit; i++)
        {
            (*this)+=tmp;
        }
    }
    else
    {
        digits=char(0);
        sign=0;
    }
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& rhs)
{
    int this_len = digits.length();
    int rhs_len = rhs.digits.length();
    if(this_len>=rhs_len)
    {
        if(rhs_len==1)
        {
            (*this)*=(rhs.digits[0]);
        }
        else
        {
            int m2 = (this_len>>1);
            BigInt highM(digits.substr(m2), 1, base);
            BigInt lowM(digits.substr(0, m2), 1, base); lowM.normalize();
            BigInt lowm(rhs.digits.substr(0, m2), 1, rhs.base); lowm.normalize();
            BigInt highm;
            if(m2>=rhs_len)
            {
                highm = BigInt::ZERO(rhs.base);
            }
            else
            {
                highm = BigInt(rhs.digits.substr(m2), 1, rhs.base);
            }
            BigInt z0(lowM * lowm);
            BigInt z1((lowM+highM)*(lowm+highm));
            BigInt z2(highM*highm);
            (*this) = (z2<<(2*m2))+((z1-z2-z0)<<(m2))+(z0);
#ifdef DEBUG_MULTI
            cout<<"highM: "<<highM<<" lowM: "<<lowM<<" highm: "<<highm<<" lowm: "<<lowm<<'\n';
            cout<<"lowM+highM: "<<(lowM+highM)<<" lowm+highm: "<<(lowm+highm)<<'\n';
            cout<<"z0: "<<z0<<" z1: "<<z1<<" z2: "<<z2<<'\n';
            cout<<(z2<<(2*m2))<<((z1-z2-z0)<<(m2))<<(z0);
            cout<<"ret: "<<(*this)<<'\n';
#endif
        }
    }
    else
    {
        (*this)=(BigInt(rhs)*=(*this));
    }
    if(!this->is_netrual() && !rhs.is_positive())
        this->sign = rhs.sign;
    return *this;
}
BigInt BigInt::operator-(const BigInt& rhs)const
{
    return ((BigInt(*this))-=(rhs));
}
BigInt& BigInt::operator-=(const BigInt& rhs)
{
    return (*this)+=(-rhs);
}




int main()
{
    // 用法：BigInt(sign, "string", base=10)
    BigInt a(1, "123456789987654321");
    BigInt b(1, "654321");

    assert((a*b).to_string() == string("80780370281511962971041"));
    b.force_negative();
    assert(((a*b).to_string()) == string("80780370281511962971041"));
    assert((a*b).is_negetive());

    do
    {   // 50以下数的阶乘
        vector<BigInt> vbi;
        BigInt pro(1);
        for(int i=1; i<=50; i++)
        {
            vbi.push_back(BigInt(i));
            pro*=vbi[i-1];
        }
        assert(pro.to_string() == string("30414093201713378043612608166064768844377641568960512000000000000"));
    }while (0);


    // 8进制举例。
    BigInt a8(1, "47", 8);
    BigInt b8(1, "11", 8);

    assert((a8*b8).to_string() == string("537"));
    assert((a8+b8).to_string() == string("60"));

    return 0;
}





// Local Variables:
// eval:(progn (hs-minor-mode t) (let ((hs-state '((549 3832 hs) (3867 4065 hs) (4117 4272 hs) (4321 6217 hs) (6269 6400 hs) (6451 6665 hs) (6714 8141 hs) (8193 8231 hs) (8280 8309 hs))) (the-mark 'scinartspecialmarku2npbmfydfnwzwnpywxnyxjr)) (dolist (i hs-state) (if (car i) (progn (goto-char (car i)) (hs-find-block-beginning) (hs-hide-block-at-point nil nil))))) (goto-char 8313) (recenter-top-bottom))
// End:
