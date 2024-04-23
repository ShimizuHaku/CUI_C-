#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>
#include <fstream>

using namespace boost::multiprecision;
typedef number<cpp_dec_float<100010>> bignum;

int main()
{
    std::ofstream outFile("output.txt");

    if (!outFile) return 1;

    const int head = 20500;
    bignum fact("1");
    bignum sum("0");
    for (int i = head; i > 0; --i){
        fact = fact*i;
        sum += fact;
        std::cout << (head-i) << "\n";
    }
    bignum e("0");
    e = sum/fact;

    outFile.precision(std::numeric_limits<bignum>::digits10);
    outFile << "e=" << e;
    outFile.close();
    return 0;
}