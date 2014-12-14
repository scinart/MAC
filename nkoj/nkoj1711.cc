//nkoj 1711
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <cstdio>

using namespace std;

// sum to 24

int mod(int N, int m)
{
    if(m*N>0)
    {
        return N%m;
    }
    else if (m*N<0)
    {
        return N%m+((N%m)?m:0);
    }
    else return 0;
}
int gcd(int a, int b)
{
    if (a<0) a=-a;
    if (b<0) b=-b;
    if (a>b)
    {
        int c=a;
        a=b;
        b=c;
    }
    if (a==0)
        return b;
    return gcd(mod(b,a),a);
}

class Rational;
class Rational
{
public:
    int p; //numerator
    int q; //denominator
    const static Rational ZERO;
    const static Rational ONE;
    Rational(){}
    Rational(int a):p(a),q(1){}
    Rational(int a,int b):p(a),q(b){}
    bool operator==(const Rational & rhs)const {return p==rhs.p && q==rhs.q; }
    bool operator==(int rhs)const {return p==rhs && q==1; }
    bool operator!=(const Rational & rhs)const {return ! this->operator==(rhs);}
    bool operator>(const Rational& rhs)const {return (this->operator-(rhs)).p > 0;}
    bool operator<(const Rational& rhs)const {return (this->operator-(rhs)).p < 0;}
    Rational operator+(const Rational & rhs)const
    {
        Rational a;
        a.p = this->p*rhs.q + this->q*rhs.p;
        a.q = this->q*rhs.q;
        a.formalize();
        return a;
    }
    Rational operator-(const Rational & rhs)const
    {
        Rational a;
        a.p = this->p*rhs.q - this->q*rhs.p;
        a.q = this->q*rhs.q;
        a.formalize();
        return a;
    }
    Rational operator*(const Rational & rhs)const
    {
        Rational a;
        a.p = this->p*rhs.p;
        a.q = this->q*rhs.q;
        a.formalize();
        return a;
    }
    Rational operator/(const Rational & rhs)const
    {
        assert(rhs != Rational::ZERO);
        Rational a;
        a.p = this->p*rhs.q;
        a.q = this->q*rhs.p;
        a.formalize();
        return a;
    }
    operator string ()const
    {
        stringstream ss;
        if (q == 1)
        {
            ss<<p;
        }
        else
        {
            ss<<p<<"/"<<q;
        }
        return string(ss.str());
    }

    friend ostream& operator<<(ostream& os, const Rational & rhs)
    {
        if(rhs.q==1)
        {
            os<<rhs.p;
        }
        else
        {
            os<<rhs.p<<"/"<<rhs.q;
        }
        return os;
    }
private:
    void formalize()
    {
        int d=gcd(p,q);
        p/=d;
        q/=d;
    }

};

const Rational Rational::ZERO(0,1);
const Rational Rational::ONE(1,1);

int a,b,c,d;

/**
   return true if vector[pos...end) can form res;
*/
bool get(vector<Rational>& vr, int pos, Rational res, string& ss)
{
    if(pos == vr.size()-1)
    {
        if (vr[pos] == res)
        {
            ss += vr[pos];
            return true;
        }
        else return false;
    }
    else if(get(vr,pos+1,res-vr[pos], ss))
    {
        ss = "(" + ss + "+" + string(vr[pos]) + ")";
        return true;
    }
    else if(get(vr,pos+1,res+vr[pos], ss))
    {
        ss = "(" + ss + "-" + string(vr[pos]) + ")";
        return true;
    }
    else if(get(vr,pos+1,vr[pos]-res, ss))
    {
        ss = "(" + string(vr[pos]) + "-" + ss + ")";
        return true;
    }
    else if(get(vr,pos+1,res/vr[pos], ss))
    {
        ss = "(" + ss + "*" + string(vr[pos]) + ")";
        return true;
    }
    else if(res != 0 && get(vr,pos+1,vr[pos]/res, ss))
    {
        ss = "(" + string(vr[pos]) + "/" + ss + ")";
        return true;
    }
    else if(get(vr,pos+1,res*vr[pos], ss))
    {
        ss = "(" + ss + "/" + string(vr[pos]) + ")";
        return true;
    }

    else return false;
}

bool getwithperm(vector<Rational>& vr,int pos, Rational res, string& ss)
{
    for(int i=0; i<4*3*2*1; i++)
    {
        if (get(vr, pos, res, ss))
            return true;
        next_permutation(vr.begin(), vr.end());
    }
    return false;
}



int main()
{
    //freopen("nkoj1711.in", "r", stdin);
    int cases = 0;
    while(cin>>a>>b>>c>>d)
    {
        cases++;
        vector<Rational> vr;
        vr.push_back(a);
        vr.push_back(b);
        vr.push_back(c);
        vr.push_back(d);
        sort(vr.begin(), vr.end());
        cout<<"Case "<<cases<<":\n";
        string ss;
        if (getwithperm(vr,0,24,ss))
        {
            cout<<ss<<endl;
        }
        else
        {
            cout<<"No Solution!"<<endl;
        }

    }
    return 0;
}
