#include <iostream>

int main()
{
#ifdef __STRICT_ANSI__
    int a,b;
    while(std::cin>>a>>b)
    {
        std::cout<<(a+b)<<std::endl;
    }
#else
    std::cout<<0<<std::endl;
#endif
}
