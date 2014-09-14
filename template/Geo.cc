#include <cmath>
#include <algorithm>
const double eps=1e-8;
const double pi=3.1415926535897932384626;

int sign(double x){//控制精度
    if(fabs(x)<=eps) return 0;
    else return x<0?-1:1;
}
class Point{
public:
    double x,y;
    Point(){}
    Point(double a,double b):x(a),y(b){}
    bool operator<(const Point&p) const {// 小於。依座標大小排序，先排 x 再排 y。
        int c = sign(x - p.x);
        if (c) return c == -1;
        else return sign(y - p.y) == -1;
    }
    bool operator==(const Point& b)const{return sign(x-b.x)==0 && sign(y-b.y)==0;}
};
typedef Point Vector;
struct Line
{
    Point s,e,v;
    Line(Point p,Vector vec,int):s(p),v(vec){e=s+v;}//法向量式
    Line(Point s,Point e):s(s),e(e){v=e-s;}//两点式
};

Point rotate(const Point& P,double theta){ // return [cos(θ) -sin(θ); sin(θ) cos(θ)]*P;
    double c = cos(theta), s = sin(theta);
    return Point(c*P.x-s*P.y,s*P.x+c*P.y);
}
Vector operator+(const Vector& A,const Vector& B){return Vector(A.x+B.x,A.y+B.y);}
Vector operator-(const Vector& A,const Vector& B){return Vector(A.x-B.x,A.y-B.y);}
Vector operator*(const Vector& A,double p){return Vector(A.x*p,A.y*p);}
Vector operator/(const Vector& A,double p){return Vector(A.x/p,A.y/p);}
Vector normal(const Vector& A){ //单位法线 (左转90度后的单位向量) //调用需确定A为非零向量
    double L = length(A);
    return Vector(-A.y/L , A.x/L);
}

double cross(const Vector& A,const Vector&B){return A.x*B.y-A.y*B.x;}//cross product.
double cross(const Point& O,const Point&A, const Point& B){return cross(A-O,B-O);}
double dot(const Vector& A,const Vector&B){return A.x*B.x+A.y*B.y;}//dot product.
double length(const Vector& A){return sqrt(dot(A,A));}
double angle(const Vector& A,const Vector&B){
    if(cross(A,B)>0) return acos(dot(A,B)/length(A)/length(B));
    else return 2*pi-acos(dot(A,B)/length(A)/length(B));
} //angle from vector A to vector B counterclockwisely.
template<typename T>double PolygonArea(T p, int n){//多边形有向面积 支持非凸多边形
    double area = 0;
    for(int i=1; i<n-1; i++) area+=cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

int lineIntersect(const Line& a,const Line& b, Point& res){
    double denorm = cross(a.v,b.v);
    if(sign(denorm)==0) return -1;
    Vector u=a.s-b.s;
    double t = cross(b.v,u) / cross(a.v,b.v);
    res = a.s+a.v*t;
    return 0;
}
bool parallel(const Line& a,const Line& b){return sign(cross(a.v,b.v))==0;}//直线平行
bool onSegment(const Line& a,const Point& p){return sign(cross(a.s-p,a.e-p)==0 && sign(dot(a.s-p,a.e-p))<0);}

#ifdef CONVEX_HULL
const int MAXN=100;
Point P[MAXN], CH[MAXN*2];
void Andrew_monotone_chain(int numpoint){// 將所有點依照座標大小排序
    // m 為凸包頂點數目
    // 包下半部
    // 包上半部，不用再包入方才包過的終點，但會再包一次起點
    // 最後一個點是重複出現兩次的起點，故要減一。
    std::sort(P, P+numpoint);
    int m = 0;
    for (int i=0; i<numpoint; CH[m++]=P[i++]) while (m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;
    for (int i=numpoint-2, t=m+1; i>=0; CH[m++]=P[i--]) while (m >= t && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;
    m--;
}
#endif

int main(){}


// Local Variables:
// eval:(progn (hs-minor-mode t) (let ((hs-state '((130 188 hs) (347 455 hs) (795 882 hs) (1260 1322 hs) (1676 1798 hs) (1854 1854 hs) (1922 2028 hs) (2090 2265 hs) (2582 2947 hs))) (the-mark 'scinartspecialmarku2npbmfydfnwzwnpywxnyxjr)) (dolist (i hs-state) (if (car i) (progn (goto-char (car i)) (hs-find-block-beginning) (hs-hide-block-at-point nil nil))))) (goto-char 1905) (recenter-top-bottom))
// End:
