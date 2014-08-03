template <typename T> inline T zip(T a,T b){return (a<<(sizeof(T)*CHAR_BIT/2))|b;}
template <typename T> inline T high (T a){return a>>(sizeof(T)*CHAR_BIT/2);}
template <typename T> inline T low (T a){return a&((((T)1)<<(sizeof(T)*CHAR_BIT/2))-1);}

