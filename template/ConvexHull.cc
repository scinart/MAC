const int MAXN = ...;
// P為平面上散佈的點。設定為MAXN點。
// CH為凸包上的頂點。設定為逆時針方向排列。可以視作一個stack。
struct Point {int x, y;} P[MAXN], CH[MAXN*2];

// 向量OA叉積向量OB。大於零表示從OA到OB為逆時針旋轉。
double cross(Point& o, Point& a, Point& b)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 小於。依座標大小排序，先排 x 再排 y。
bool compare(Point& a, Point& b)
{
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

void Andrew_monotone_chain()
{
    // 將所有點依照座標大小排序
    sort(P, P+MAXN, compare);

    int m = 0;  // m 為凸包頂點數目

    // 包下半部
    for (int i=0; i<MAXN; ++i)
    {
        while (m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;
        // 
        CH[m++] = P[i];
    }

    // 包上半部，不用再包入方才包過的終點，但會再包一次起點
    for (int i=MAXN-2, t=m+1; i>=0; --i)
    {
        while (m >= t && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;
        CH[m++] = P[i];
    }

    m--;    // 最後一個點是重複出現兩次的起點，故要減一。
}
