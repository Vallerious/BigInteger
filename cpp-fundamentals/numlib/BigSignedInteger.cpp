//
// Created by valeri on 1.02.21 г..
//
#include <string>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

class BigSignedInteger {
private:
    std::string digits;
    unsigned int digitsCount;

    bool isValid(std::string digits) {
        if (digits.empty() || digits.at(0) != '-') {
            return false;
        }

        for (char digit : digits) {
            if (!std::isdigit(digit)) {
                return false;
            }
        }

        return true;
    }
public:
    BigSignedInteger(std::string digits): digits(digits) {
        if (!isValid(digits)) {
            throw std::invalid_argument("parameter cannot be empty or negative and must be a valid integer");
        }
        digitsCount = digits.size();
    }

    std::string toString() const {
        return digits;
    }

    BigSignedInteger operator+(const BigSignedInteger& other) {
        int idxA = digitsCount - 1;
        int idxB = other.digitsCount - 1;
        std::string sumStr;
        sumStr.reserve(std::max(digitsCount, other.digitsCount));
        short carry = 0;

        while (idxA >= 0 || idxB >= 0) {
            short ac = idxA < 0 ? 0 : digits.at(idxA) - '0';
            short bc = idxB < 0 ? 0 : other.digits.at(idxB) - '0';

            short digitSum = ac + bc + carry;

            if (digitSum > 9) {
                carry = 1;
                digitSum = digitSum % (short)10;
            } else {
                carry = 0;
            }

            sumStr = std::to_string(digitSum) + sumStr;

            idxA -= 1;
            idxB -= 1;
        }

        if (carry > 0) {
            sumStr = "1" + sumStr;
        }

        return BigSignedInteger(sumStr);
    }

    friend std::ostream& operator<<(std::ostream& os, BigSignedInteger& bsi) {
        os << bsi.toString();
        return os;
    }
};