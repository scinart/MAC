// Class of Pairs

template <typename T>
class PTT
{
public:
    T first;
    T second;
    PTT (T a, T b){
        first = a;
        second = b;
    }
    PTT& operator=(const PTT& rhs)
    {
        first = rhs.first;
        second = rhs.second;
    }
    bool operator==(const PTT& rhs)const
    {
        return first==rhs.first && second == rhs.second;
    }
    bool operator<(const PTT& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second);
    }
};

template <typename T>
class PTTTT
{
public:
    T first;
    T second;
    T third;
    T fourth;
    PTT (T a, T b,T c,T d){
        first = a;
        second = b;
        third = c;
        fourth = d;
    }
    PTT& operator=(const PTTTT& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        third=rhs.third;
        fourth=rhs.fourth;
    }
    bool operator==(const PTTTT& rhs)const
    {
        return first==rhs.first && second == rhs.second &&
            third==rhs.third && fourth == rhs.fourth;
    }
    bool operator<(const PTTTT& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second) ||
            (first==rhs.first && second == rhs.second && third < rhs.third) ||
            (first==rhs.first && second == rhs.second && third == rhs.third && fourth<rhs.fourth);
    }
};


template <typename T>
class PTTT
{
public:
    T first;
    T second;
    T third;
    PTTT (T a, T b,T c){
        first = a;
        second = b;
        third = c;
    }
    PTTT& operator=(const PTTT& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        third=rhs.third;
    }
    bool operator==(const PTTT& rhs)const
    {
        return first==rhs.first && second == rhs.second && third==rhs.third;
    }
    bool operator<(const PTTT& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second) ||
            (first==rhs.first && second == rhs.second && third < rhs.third);
    }
};
