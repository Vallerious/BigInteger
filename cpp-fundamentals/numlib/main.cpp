#include <iostream>
#include "BigInteger.cpp"

int main() {
    BigInteger a("239");
    BigInteger b("-239");

    BigInteger result = a - b;

    std::cout << "Result is: " << result << std::endl;

    return 0;
}
