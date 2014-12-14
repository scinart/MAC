// C++ Big integer Class.
// created: 2014-06-27 18:46:37
// Time-stamp: <2014-06-28 11:15:30 scinart>
// AC.

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
public:
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
    BigInt(int_8 s, string d):digits(d),sign(s),base(10){//base10 专用
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_);
    }
    BigInt(const BigInt& rhs):digits(rhs.digits),sign(rhs.sign),base(rhs.base){}
    BigInt(int i):digits(SSTR(i)),sign(i>0), base(10) {//base10 专用
        std::reverse(digits.begin(), digits.end());
        for_each(digits.begin(),digits.end(),dec_0_);
    }

    friend ostream& operator<<(ostream& os, const BigInt& bi)
    { //base10 专用
        string str(bi.digits);
        std::reverse(str.begin(), str.end());
        for_each(str.begin(),str.end(),inc_0_);
        // return os<<str<<' '<<(bi.sign>=0?'+':'-')<<'\n';
        return ((bi.sign<0)?(os<<'-'<<str):(os<<str));
    }

    BigInt& normalize();

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
    BigInt& operator*=(const BigInt& rhs);
    BigInt& operator*=(const uint_8& rhs);
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
                int_8 sum=10+digits[i]-rhs.digits[i]-carry;
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
    {
        return (BigInt(*this)*=rhs);
    }
    else
    {
        return (BigInt(rhs)*=(*this));
    }
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
            return (*this)*=(rhs.digits[0]);
        }
        else
        {
            int m2 = (this_len>>1);
            BigInt highM(digits.substr(m2), sign, base);
            BigInt lowM(digits.substr(0, m2), sign, base); lowM.normalize();
            BigInt lowm(rhs.digits.substr(0, m2), rhs.sign, rhs.base); lowm.normalize();
            BigInt highm;
            if(m2>=rhs_len)
            {
                highm = BigInt::ZERO(rhs.base);
            }
            else
            {
                highm = BigInt(rhs.digits.substr(m2), rhs.sign, rhs.base);
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

    string s1,s2; int pwd;
    while(cin>>s1>>pwd)
    {
        s2 = s1.substr(s1.find_first_of('.')+1);
        s1 = s1.substr(0,s1.find_first_of('.'));
        s2 = s2.substr(0, s2.find_last_not_of('0')+1);

        // cout<<s1<<'.'<<s2<<'\n';
        int i2bit = s2.length();
        bool nos1=false;
        if(i2bit)
        {
            if(s1=="0")
            {
                s1=s2;
                nos1=true;
            }
            else
                s1 += s2;
        }


        BigInt b1(1,s1);
        BigInt bb1(b1);

        for(int i=0; i<pwd-1; i++)
        {
            bb1*=b1;
        }
        string ans = SSTR(bb1);

        if(!i2bit)
        {
            cout<<ans<<'\n';
        }
        else if (nos1)
        {
            string padding_zero(pwd*i2bit-ans.length(),'0');
            cout<<'.'<<padding_zero<<ans<<'\n';
        }
        else
        {
            string ans1 = ans.substr(0,ans.length()-i2bit*pwd);
            string ans2 = ans.substr(ans.length()-i2bit*pwd);
            cout<<ans1<<'.'<<ans2<<'\n';
        }

    }
    return 0;
}
