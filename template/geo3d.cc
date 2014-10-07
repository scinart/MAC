#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
namespace Geometry{
const double eps=1e-9;
const double pi=acos(-1.0);
int dcmp(double d)
{
    if (fabs(d)<=eps)return 0;
    return d>eps?1:-1;
}
struct Point;
typedef Point Vector;
struct Line;
struct Plane;

struct Point
{
    double x,y,z;
    Point(){}
    Point(double x_,double y_,double z_):x(x_),y(y_),z(z_){}
    void input(){scanf("%lf%lf%lf",&x,&y,&z);}
    void show(){printf("%.4lf %.4lf %.4lf\n",x,y,z);}
    bool operator==(const Point& a)const{return dcmp(a.x-x)==0&&dcmp(a.y-y)==0&&dcmp(a.z-z)==0;}
    bool operator< (const Point& a)const{return dcmp(a.x-x)==0?dcmp(y-a.y)==0?dcmp(z-a.z)<0:y<a.y:x<a.x;}
    double len()const{return sqrt(len2());}
    double len2()const{return x*x+y*y+z*z;}
    double distance(const Point& p)const{return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)+(p.z-z)*(p.z-z));}
    Point add(const Point& p)const{return Point(x+p.x,y+p.y,z+p.z);}
    Point sub(const Point& p)const{return Point(x-p.x,y-p.y,z-p.z);}
    Point operator + (const Point & p) const{return Point(x+p.x,y+p.y,z+p.z);}
    Point operator - (const Point & p) const{return Point(x-p.x,y-p.y,z-p.z);}
    Point mul(double d)const{return Point(x*d,y*d,z*d);}
    Point div(double d)const{return Point(x/d,y/d,z/d);}
    double dot(const Point& p)const{return x*p.x+y*p.y+z*p.z;}
    double operator* (const Point& p)const{return x*p.x+y*p.y+z*p.z;}
    Point cross(const Point& p)const{return Point(y*p.z-p.y*z,p.x*z-x*p.z,x*p.y-p.x*y);}
    Point operator^  (const Point& p)const{return Point(y*p.z-p.y*z,p.x*z-x*p.z,x*p.y-p.x*y);}
    //double rad(Point a,Point b){Point p=(*this);return acos(a.sub(p).dot(b.sub(p))/(a.distance(p)*b.distance(p)));}
    double rad(const Vector& v)const
    {
        const Vector& u=*this;
        return acos((u*v)/(u.len()*v.len()));
    }
    double rad(const Vector& v, const Vector& direct)const
    {
        const Vector& u=*this;
        if((u^v)*direct>0)
            return rad(v);
        else
            return 2*pi-rad(v);
    }
    Point trunc(double r){r/=len();return Point(x*r,y*r,z*r);} //set length to r;
};
struct Line
{
    Point a,b;
    Line(){}
    Line(Point _a,Point _b):a(_a),b(_b){}
    bool operator==(Line v){return (a==v.a)&&(b==v.b);}
    void input(){a.input();b.input();}
    double length(){return a.distance(b);}
    bool pointonseg(Point p){return dcmp(p.sub(a).cross(p.sub(b)).len())==0&&dcmp((a-p).dot(b-p))<=0;}
    double dispointtoline(Point p){return b.sub(a).cross(p.sub(a)).len()/a.distance(b);}
    double dispointtoseg(Point p)
    {
        if(dcmp((p-b)*(a-b))<0||dcmp((p-a)*(b-a))<0)
            return min(p.distance(a),p.distance(b));
        else
            return dispointtoline(p);
    }
    double dislinetoline(const Line& v)const
    {
        Point n=(a-b)^(v.a-v.b);
        return fabs(((a-v.a)*n))/n.len();
    }


    Point lineprojection(Point p){return a.add(b.sub(a).trunc(b.sub(a).dot(p.sub(a))/b.distance(a)));}
    Point rotate(Point p,double ang)//p绕此向量逆时针arg弧度
    {
        if (dcmp((p.sub(a).cross(p.sub(b)).len()))==0)return p;
        Point f1=b.sub(a).cross(p.sub(a));
        Point f2=b.sub(a).cross(f1);
        double len=fabs(a.sub(p).cross(b.sub(p)).len()/a.distance(b));
        f1=f1.trunc(len);f2=f2.trunc(len);
        Point h=p.add(f2);
        Point pp=h.add(f1);
        return h.add((p.sub(h)).mul(cos(ang))).add((pp.sub(h)).mul(sin(ang)));
    }
    Point crossline (const Line& v)const // 两直线交点
    {
        const Line& u=*this;
        Point ret=u.a;
        double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x)) /
                 ((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
        Vector go((u.b.x-u.a.x),(u.b.y-u.a.y),(u.b.z-u.a.z));
        return ret+go.mul(t);
    }
};
struct Plane
{
    Point a,b,c;
    Vector o;
    Plane(){}
    Plane(Point _a,Point _b,Point _c):a(_a),b(_b),c(_c){o=pvec();}
    Plane(double _a,double _b,double _c,double _d) //ax+by+cz+d=0
    {
        o=Point(_a,_b,_c);
        if (dcmp(_a)!=0){a=Point((-_d-_c-_b)/_a,1,1);}
        else if (dcmp(_b)!=0){a=Point(1,(-_d-_c-_a)/_b,1);}
        else if (dcmp(_c)!=0){a=Point(1,1,(-_d-_a-_b)/_c);}
    }
    void input(){a.input();b.input();c.input();o=pvec();}
    Vector pvec()const{return b.sub(a).cross(c.sub(a));} //perpendicular vector;
    bool pointonPlane(const Point& p)const{return dcmp(p.sub(a).dot(o))==0;}//点是否在平面上
    int pointontriangle(const Point& p)const//点是否在空间三角形abc上
    {
        if (!pointonPlane(p))return 0; //0 不在
        double s=a.sub(b).cross(c.sub(b)).len();
        double s1=p.sub(a).cross(p.sub(b)).len();
        double s2=p.sub(a).cross(p.sub(c)).len();
        double s3=p.sub(b).cross(p.sub(c)).len();
        if (dcmp(s-s1-s2-s3))return 0; //0 不在
        if (dcmp(s1)&&dcmp(s2)&&dcmp(s3))return 2; //2 在内部
        return 1; //1 在边界上
    }
    //判断两平面关系,三点共线无意义
    //-1 垂直
    //0 相交
    //1 平行但不重合
    //2 重合
    bool relationPlane(const Plane& f)const
    {
        if (dcmp(o.cross(f.o).len())){
                if (dcmp(pvec().dot(f.pvec())) == 0) return -1;
                return 0;
        }
        if (pointonPlane(f.a))return 2;
        return 1;
    }
    double anglePlane(const Plane& f)const//两平面夹角
    {
        return acos(o.dot(f.o)/(o.len()*f.o.len()));
    }
    double dispoint(const Point& p)const//点到平面距离
    {
        return fabs(p.sub(a).dot(o)/o.len());
    }
    Point pttoPlane(const Point& p)const//点到平面最近点
    {
        Line u=Line(p,p.add(o));
        return crossline(u,p);
    }
    Point crossline(const Line& u,const Point &p)const //平面和直线的交点
    {
        double x=o.dot(u.b.sub(a));
        double y=o.dot(u.a.sub(a));
        double d=x-y;
        return u.a.mul(x).sub(u.b.mul(y)).div(d);
    }
    Line crossPlane(const Plane& f)const//平面和平面的交线
    {
        Point oo=o.cross(f.o);
        Point v=o.cross(oo);
        double d=fabs(f.o.dot(v));
        if (dcmp(d)==0)return Line();
        Point q=a.add(v.mul(f.o.dot(f.a.sub(a))/d));
        return Line(q,q.add(oo));
    }

};

//判点是否在空间三角形上,包括边界,三点共线无意义
int dot_inPlane_in(const Point& p,const Plane& s){ // 面积法
    return dcmp((((s.a-s.b)^(s.a-s.c)).len())-
                (((p-s.a)^(p-s.b)).len())-
                (((p-s.b)^(p-s.c)).len())-
                (((p-s.c)^(p-s.a)).len()))==0;
}

};

using namespace Geometry;
