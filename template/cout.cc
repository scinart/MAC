#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    double f = 12345.6789;

    std::cout << std::setprecision(3) << f << '\n'; //1.23e+04
    std::cout << std::setprecision(7) << f << '\n'; //12345.68
    std::cout << std::fixed;
    std::cout << std::setprecision(3) << f << '\n'; //12345.679
    std::cout << std::setprecision(7) << f << '\n'; //12345.6789000







    return 0;
}

