// -*- coding: utf-8 -*-
// C++ Big integer Class.
// created: 2014-06-27 18:46:37
// Time-stamp: <2014-09-17 17:57:33 scinart>

#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>

#define SSTR( x ) dynamic_cast<std::ostringstream&>((std::ostringstream()<<std::dec<<x)).str()

#ifdef __GNUC__
  #if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
    #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
  #else
    #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
  #endif
#else
  #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
#endif


typedef unsigned char uint_8;
typedef signed char int_8;
inline void dec_0_(char& c){c-='0';}
inline void inc_0_(char& c){c+='0';}
inline void inc_0_A(char& c){if(c>9)c+=('A'-10);else c+='0';}
inline void dec_0_A(char& c){if(c>'A')c-=('A'-10);else c-='0';}
bool char_is_not_0(char c){return c;}


using namespace std;
class BigInt
{
public:
    // digits are stored in reversed order.
    string digits;
    int_8 sign;
    const uint_8 base;
public:

    const static BigInt ZERO(uint_8 b){return BigInt(char(0),0,b);}
    const static BigInt ONE(uint_8 b){return BigInt(char(1),1,b);}

    BigInt():digits(1,char(0)),sign(0),base(10){}
    BigInt(char c, int_8 s, uint_8 b=10):digits(1,c),sign(s),base(b){}
    BigInt(int_8 s, string d, uint_8 b=10):digits(d),sign(s),base(b){
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_A);
    }
    BigInt(const BigInt& rhs):digits(rhs.digits),sign(rhs.sign),base(rhs.base){}
    BigInt(long long u):base(10)
    {
        int v=u;if(v<0)v=-v; digits=(SSTR(v));
        if(u>0)sign=1;else sign=(u?-1:0);
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_);
    }

    friend ostream& operator<<(ostream& os, const BigInt& bi)
    {
        return os<<(bi.to_string());
    }
    string to_string()const
    {   //base36或以下 专用
        string str(digits);
        std::reverse(str.begin(), str.end());
        for_each(str.begin(),str.end(),inc_0_A);
        return ((sign<0)?('-'+str):(str));
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
    BigInt operator/(const BigInt& rhs)const;
    BigInt divDigit(const uint_8& digit)const;
private:
    BigInt& operator/=(const uint_8& digit);
public:
    BigInt& operator/=(const BigInt& rhs);
    BigInt operator%(const BigInt& rhs)const;
    BigInt& operator%=(const BigInt& rhs);
    bool divideBy(const BigInt& div,BigInt& q,BigInt& re);

    BigInt& operator++(){(*this)+=ONE(base);return *this;}
    const BigInt operator++(int){BigInt ret(*this);*this+=ONE(base);return ret;}
    BigInt& operator--(){*this-=ONE(base);return *this;}
    const BigInt operator--(int){BigInt ret(*this);*this-=ONE(base);return ret;}
public:
    bool operator<(const BigInt& rhs)const;
    bool operator<=(const BigInt& rhs)const;
    bool operator>(const BigInt& rhs)const;
    bool operator>=(const BigInt& rhs)const;
    bool operator==(const BigInt& rhs)const;
    bool operator!=(const BigInt& rhs)const;

    BigInt& operator<<=(int bits){if(sign) {string s(bits,char(0)); digits=s+digits;} return *this;}
    BigInt& operator>>=(int bits){if(sign) {digits = digits.substr(bits);} return *this;}
    BigInt operator<<(int bits)const{return ((BigInt(*this))<<=bits);}
    BigInt operator>>(int bits)const{return ((BigInt(*this))>>=bits);}

private:
    BigInt(string d, int_8 s, uint_8 b):digits(d),sign(s),base(b){}

};

template <class GEN>
BigInt lbound (BigInt& first, BigInt& last, const BigInt& val, GEN gen)
{
    BigInt it;
    BigInt count, step;
    count = last-first;
    while (count.sign>0)
    {
        it = first; step=count/2; it+=step;
        if (gen(it)<val)
        {
            first=++it;
            count-=step+1;
        }
        else count=step;
    }
    return first;
}
template <class GEN>
BigInt uboundabs (BigInt first, BigInt last, const BigInt& val, GEN gen)
{
    BigInt it;
    BigInt count, step;
    count=last-first;
    while (count.sign>0)
    {
        it = first; step=count.divDigit(2); it+=step;
        if (!(val.abslt(gen(it))))
        {
            first=++it;
            count-=step+1;
        }
        else count=step;
    }
  return first;
}


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
    uint_8 this_sign = sign;
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
    if(!this->is_netrual() && rhs.is_negetive())
        this->sign = -this_sign;
    else if(rhs.is_netrual())
        this->sign = 0;
    else
        this->sign = this_sign;
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
BigInt BigInt::divDigit(const uint_8& rhs)const
{
    return BigInt(*this)/=rhs;
}
BigInt BigInt::operator/(const BigInt& rhs)const
{
    assert(rhs.sign);
    BigInt ret(BigInt::ZERO(base));
    if(!(abslt(rhs)))
    {
        int len=this->digits.length();
        int rlen=rhs.digits.length();
        BigInt lb(BigInt::ONE(base)<<(len-rlen));
        BigInt rb(lb);
        // pro > this : -lb
        // pro == this : +ub
        // pro < this : +ub
        if(abslt(lb*rhs)) lb>>=1;
        else rb<<=1;
        ret = --uboundabs(lb, rb, *this, [&rhs](const BigInt& pt){return pt*rhs;});
    }
    if((rhs.sign>0 && sign<0) || (rhs.sign<0 && sign>0))
    {
        ret.take_negative();
        if((*this).digits!=(rhs*ret).digits) --ret;
    }
    return ret;
}
BigInt& BigInt::operator/=(const uint_8& digit)
{
    uint_8 carry=0;
    REACH(it,digits)
    {
        unsigned p=carry*base+*it;
        unsigned pt=p/digit;
        carry=p%digit;
        *it=(uint_8)pt;
    }
    normalize();
    return *this;
}
BigInt& BigInt::operator/=(const BigInt& rhs)
{
    (*this)=(*this)/rhs;
    return *this;
}
BigInt BigInt::operator%(const BigInt& rhs)const
{
    return (*this)-(*this)/rhs*rhs;
}
BigInt& BigInt::operator%=(const BigInt& rhs)
{
    (*this)=(*this)%rhs;
    return *this;
}
bool BigInt::operator<(const BigInt& rhs)const
{
    if(sign<rhs.sign)return true;
    if(sign>rhs.sign)return false;
    if(sign==0)return false;
    if(sign>0)return abslt(rhs);
    else return !abslt(rhs);
}
bool BigInt::operator<=(const BigInt& rhs)const
{
    return !(rhs<(*this));
}
bool BigInt::operator>(const BigInt& rhs)const
{
    return rhs.operator<(*this);
}
bool BigInt::operator>=(const BigInt& rhs)const
{
    return !(*this<rhs);
}
bool BigInt::operator==(const BigInt& rhs)const
{
    if(sign!=rhs.sign)return false;
    int this_len = digits.length();
    int rhs_len = rhs.digits.length();
    if(this_len>rhs_len) return false;
    if(this_len<rhs_len) return false;
    for(int i=this_len-1; i>=0; i--)
    {
        if(digits[i]<rhs.digits[i]) return false;
        if(digits[i]>rhs.digits[i]) return false;
    }
    return true;
}
bool BigInt::operator!=(const BigInt& rhs)const
{
    return !(*this==rhs);
}



int main()
{
    // 用法：BigInt(sign, "string", base=10)
    BigInt a(1, "123456789987654321");
    BigInt b(1, "654321");

    assert((a*b).to_string() == string("80780370281511962971041"));
    b.force_negative();
    assert(((a*b).to_string()) == string("-80780370281511962971041"));
    assert((a*b).is_negetive());

    do
    {   // 50以下数的阶乘
        BigInt pro(1);
        for(int i=1; i<=50; i++)
            pro*=BigInt(i);
        assert(pro.to_string() == string("30414093201713378043612608166064768844377641568960512000000000000"));
    }while (0);


    // 8进制举例。
    BigInt a8(1, "47", 8);
    BigInt b8(1, "11", 8);

    assert((a8*b8).to_string() == string("537"));
    assert((a8+b8).to_string() == string("60"));

    int a8cnt=0;
    while(a8-->0) a8cnt++;
    assert(a8cnt==047);


    string x,y;
    while(cin>>x>>y)
    {
        BigInt xx(1,x),yy(1,y);
        cout<<xx*yy<<' '<<xx/yy<<' '<<xx%yy<<'\n';
    }
    // cout<<a8/b8<<'\n';
    // cout<<a8%b8<<'\n';
    // cout<<a8/(-b8)<<'\n';
    // cout<<a8%(-b8)<<'\n';
    return 0;
}





// Local Variables:
// eval:(progn (hs-minor-mode t) (let ((hs-state '((1651 1763 hs) (1884 2084 hs) (2154 2196 hs) (2248 2419 hs) (2934 3297 hs) (5090 5374 hs) (5804 6002 hs) (6054 6209 hs) (6258 8154 hs) (8206 8337 hs) (8388 8602 hs) (8651 10203 hs) (10255 10293 hs) (10342 10371 hs) (10422 10454 hs) (10506 11139 hs) (11190 11390 hs) (11439 11483 hs) (11535 11572 hs) (11621 11665 hs) (11715 11876 hs) (11927 11955 hs) (12005 12039 hs) (12090 12116 hs) (12167 12523 hs) (12574 12601 hs))) (the-mark 'scinartspecialmarku2npbmfydfnwzwnpywxnyxjr)) (dolist (i hs-state) (if (car i) (progn (goto-char (car i)) (hs-find-block-beginning) (hs-hide-block-at-point nil nil))))) (goto-char 14160) (recenter-top-bottom))
// End:
