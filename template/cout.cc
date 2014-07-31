#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    double d = 12345.6789;

    std::cout << std::setprecision(5) << f << '\n';
    std::cout << std::setprecision(9) << f << '\n';
    std::cout << std::fixed;
    std::cout << std::setprecision(5) << f << '\n';
    std::cout << std::setprecision(9) << f << '\n';

    return 0;
}

