#include <random>
#include <chrono>
class RandInt{
public:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    RandInt(int b,int e):generator(std::chrono::system_clock::now().time_since_epoch().count()),distribution(b,e)
    {
    }
    operator int(){
        return distribution(generator);
    }
};
