#include <iostream>
#include "BigInteger.h"
#include <assert.h>
#include "PrependString.h"
#include <chrono>
#include <fstream>
#include <vector>
#include <stdlib.h>

int main() {

    /*
     * Unit Tests
     *
     * 1. compare
     */

    BigInteger cmp1("1");
    BigInteger cmp2("2");

    assert(cmp1.compare(cmp2) < 0);
    assert(cmp2.compare(cmp1) > 0);

    BigInteger cmp3("-1");
    BigInteger cmp4("1");

    assert(cmp3.compare(cmp4) < 0);
    assert(cmp4.compare(cmp3) > 0);

    BigInteger cmp5("0");
    BigInteger cmp6("1");

    assert(cmp5.compare(cmp6) < 0);
    assert(cmp6.compare(cmp5) > 0);

    BigInteger cmp7("1");
    BigInteger cmp8("1");

    assert(cmp7.compare(cmp8) == 0);
    assert(cmp8.compare(cmp7) == 0);

    BigInteger cmp9("11");
    BigInteger cmp10("15");

    assert(cmp9.compare(cmp10) < 0);
    assert(cmp10.compare(cmp9) > 0);

    BigInteger cmp11("1111");
    BigInteger cmp12("999");

    assert(cmp11.compare(cmp12) > 0);
    assert(cmp12.compare(cmp11) < 0);

    BigInteger cmp13("-932");
    BigInteger cmp14("-73");

    assert(cmp13.compare(cmp14) < 0);
    assert(cmp14.compare(cmp13) > 0);

    BigInteger cmp15("-9");
    BigInteger cmp16("-9");

    assert(cmp15.compare(cmp16) == 0);
    assert(cmp16.compare(cmp15) == 0);

    BigInteger cmp17("-9873");
    BigInteger cmp18("9283");

    assert(cmp17.compare(cmp18) < 0);
    assert(cmp18.compare(cmp17) > 0);

    BigInteger cmp19("-1");
    BigInteger cmp20("-3");

    assert(cmp19.compare(cmp20) > 0);

    /*
     * isNegative()
     */
    BigInteger n1("-1");
    assert(n1.isNegative);

    BigInteger n2("1");
    assert(!n2.isNegative);

    BigInteger n3("0");
    assert(!n3.isNegative);


    BigInteger a("0");
    BigInteger b("0");

    assert((a + b) == "0");

    BigInteger a00("0");
    BigInteger b00("2");

    assert(a00 + b00 == "2");
    assert(b00 + a00 == "2");

    BigInteger a01("-2");
    BigInteger b01("0");

    assert(a01 + b01 == "-2");

    BigInteger a2("-9");
    BigInteger b2("9");

    assert((a2 + b2) == "0");
//
//
    BigInteger a3("9");
    BigInteger b3("-9");

    assert((a3 + b3) == "0");
//
    BigInteger a4("-10");
    BigInteger b4("-20");

    assert((a4 + b4) == "-30");
//
    BigInteger a5("399");
    BigInteger b5("101");

    assert((a5 + b5) == "500");
//
    BigInteger a6("30");
    BigInteger b6("-30");

    assert((a6 - b6) == "60");
//
    BigInteger a7("-30");
    BigInteger b7("30");

    assert((a7 - b7) == "-60");
//
//    // Test 'max' method
    BigInteger x("-1");
    BigInteger y("-3");

    assert(x.max(y) == "-1");

    BigInteger x2("200");
    BigInteger y2("100");

    assert(x2.max(y2) == "200");

    BigInteger x3("1000");
    BigInteger y3("999");

    assert(x3.max(y3) == "1000");

    BigInteger x4("892");
    BigInteger y4("982");

    assert(x4.max(y4) == "982");

    BigInteger x5("-3");
    BigInteger y5("5");

    assert(x5.max(y5) == "5");

    BigInteger x6("5");
    BigInteger y6("-3");

    assert(x6.max(y6) == "5");

    BigInteger x7("0");
    BigInteger y7("1");

    assert(x7.max(y7) == "1");

    BigInteger x8("1");
    BigInteger y8("0");

    assert(x8.max(y8) == "1");

    BigInteger x9("0");
    BigInteger y9("-1");

    assert(x9.max(y9) == "0");

    BigInteger x10("0");
    BigInteger y10("100");
    BigInteger x11("100");
    BigInteger y11("0");

    assert(x10.max(y10) == y10.max(x10));

    BigInteger x12("2");
    BigInteger y12("1");
    BigInteger z12("3");

    assert(x12.max(y12).max(z12) == "3");
//
//    // Subtract
    BigInteger as("30");
    BigInteger bs("10");

    assert((as - bs) == "20");

    BigInteger as1("1000");
    BigInteger bs1("1");

    assert(as1 - bs1 == "999");

    BigInteger as2("40");
    BigInteger bs2("11");

    assert(as2 - bs2 == "29");

    assert(bs2 - as2 == "-29");

    BigInteger as3("734723894792834789237489327489237489274892");
    BigInteger bs3("293829839289382938928392839289328938928398");

    // https://www.calculator.net/big-number-calculator.html was used to verify this
    assert(as3 - bs3 == "440894055503451850309096488199908550346494");

    BigInteger big1("-999999933333333333388888888888888888444444444444999999933333333333388888888888888888444444444444999999933333333333388888888888888888444444444444");
    BigInteger big2("293829839289382938928392839289328938928398293829839289382938928392839289328938928398293829839289382938928392839289328938928398293829839289382938928392839289328938928398");

    assert(big1 + big2 == "293829839289382938928391839289395605595064904940950400494050483948394844328938995064960496450400494050039504394844884493928398360496505955994050039503950400884494483954");

    // test equals override
    BigInteger eq1("12345");
    BigInteger eq2("-12345");

    assert(!(eq1 == eq2));

    BigInteger eq3("54321");
    BigInteger eq4("54321");

    assert(eq3 == eq4);

    //

    std::vector<std::string> numberStrs;
    time_t time1;
    srand((unsigned) time(&time1));

    for (int i = 0; i < 10; i++) {
        std::string n;

        for (int j = 0; j < 100000; j++) {
            int r = (rand() % 9) + 1;
            n += std::to_string(r);
        }

        numberStrs.push_back(n);
    }

    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<float, std::milli> mil;

    auto t = clock::now();

    for (int i = 0; i < numberStrs.size(); i++) {
        for (int j = 0; j < numberStrs.size(); j++) {
            BigInteger a(numberStrs.at(i));
            BigInteger b(numberStrs.at(j));

            BigInteger z = a + b;
        }
    }

    auto tprime = clock::now();

    std::cout << "Time to calculate " << numberStrs.size() * numberStrs.size() <<
      " operations = "  << mil(tprime - t).count() << " ms." << std::endl;

    // Measurements
    // 1. Using std::string = 36646.1 ms.
    // 2. Using custom PrependString class = 998.212 ms.

    // Test multiplication
    BigInteger m1("3");
    BigInteger m2("2");

    assert(m1 * m2 == BigInteger("6"));

    BigInteger m3("5");
    BigInteger m4("-5");

    assert(m3 * m4 == BigInteger("-25"));

    BigInteger m5("-4");
    BigInteger m6("-4");

    assert(m5 * m6 == "16");

    BigInteger m7("99999999");
    BigInteger m8("99999999");

    // this will take days....have to use some smarter multiplication algo
    assert(m7 * m8 == "9999999800000001");

    return 0;
}
