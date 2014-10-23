#include <random>
#include <chrono>
class RandInt{
public:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    static unsigned seed;
    RandInt(int b,int e):generator(std::chrono::system_clock::now().time_since_epoch().count()),distribution(b,e)
    {
        for(int i=0;i<31;i++) if(seed&1) seed>>=1,seed^=0x48000000u; else seed>>=1;
    }
    operator int(){
        return distribution(generator);
    }
};
int RandInt::seed = std::chrono::system_clock::now().time_since_epoch().count();
