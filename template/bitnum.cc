template <class T> inline T lowbit(T x) { return x & (-x); }
template <class T> inline int bitnum(T x) { return __builtin_popcount(x) + __builtin_popcount(x >> 32); }
template <class T> inline bool bittest(T x, int bit) { return x&(1<<bit); }
