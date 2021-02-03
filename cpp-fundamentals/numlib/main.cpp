#include <iostream>
#include "BigInteger.cpp"
#include <assert.h>

int main() {
    BigInteger a("0");
    BigInteger b("0");

    assert((a + b).toString() == "0");

    BigInteger a2("-9");
    BigInteger b2("9");

    assert((a2 + b2).toString() == "0");


    BigInteger a3("9");
    BigInteger b3("-9");

    assert((a3 + b3).toString() == "0");

    BigInteger a4("-10");
    BigInteger b4("-20");

    assert((a4 + b4).toString() == "-30");

    BigInteger a5("399");
    BigInteger b5("101");

    assert((a5 + b5).toString() == "500");

    BigInteger a6("30");
    BigInteger b6("-30");

    assert((a6 - b6).toString() == "60");

    BigInteger a7("-30");
    BigInteger b7("30");

    assert((a7 - b7).toString() == "-60");

    BigInteger a8("30");
    BigInteger b8("10");

    assert((a8 - b8).toString() == "20");

    BigInteger x("-1");
    BigInteger y("-3");

    assert(x.max(y) == "-1");


    return 0;
}
