// Class of Pairs

template <typename T>
class PII
{
public:
    T first;
    T second;
    PII (T a, T b){
        first = a;
        second = b;
    }
    PII& operator=(const PII& rhs)
    {
        first = rhs.first;
        second = rhs.second;
    }
    bool operator==(const PII& rhs)const
    {
        return first==rhs.first && second == rhs.second;
    }
    bool operator<(const PII& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second);
    }
};

template <typename T>
class PIIII
{
public:
    T first;
    T second;
    T third;
    T fourth;
    PII (T a, T b,T c,T d){
        first = a;
        second = b;
        third = c;
        fourth = d;
    }
    PII& operator=(const PII& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        third=rhs.third;
        fourth=rhs.fourth;
    }
    bool operator==(const PII& rhs)const
    {
        return first==rhs.first && second == rhs.second &&
            third==rhs.third && fourth == rhs.fourth;
    }
    bool operator<(const PII& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second) ||
            (first==rhs.first && second == rhs.second && third < rhs.third) ||
            (first==rhs.first && second == rhs.second && third == rhs.third && fourth<rhs.fourth);
    }
};
