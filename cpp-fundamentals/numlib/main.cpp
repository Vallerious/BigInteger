#include <iostream>
#include "BigInteger.cpp"

int main() {
    BigInteger a("0");
    BigInteger b("0");

    BigInteger result = a - b;

    std::cout << "Result is: " << result << std::endl;

    return 0;
}
