//
// Created by valeri on 1.02.21 г..
//
#include <string>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

class BigInteger {
private:
    std::string digits;
    unsigned int digitsCount;

    bool isValid(std::string digits) {
        if (digits.empty()) {
            return false;
        }

        int i = 0;

        if (digits.at(0) == '-') {
            i = 1;
        }

        for (int len = digits.size(); i < len; i++) {
            if (!std::isdigit(digits.at(i))) {
                return false;
            }
        }

        return true;
    }
public:
    BigInteger(std::string digits): digits(digits) {
        if (!isValid(digits)) {
            throw std::invalid_argument("parameter cannot be empty or negative and must be a valid integer");
        }
        digitsCount = digits.size();
    }

    std::string toString() const {
        return digits;
    }

    BigInteger operator+(const BigInteger& other) const {
        int idxA = digitsCount - 1;
        int idxB = other.digitsCount - 1;
        std::string sumStr;
        sumStr.reserve(std::max(digitsCount, other.digitsCount) + 1);
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

        return BigInteger(sumStr);
    }

    BigInteger operator-(BigInteger& other) const {
        char thisStartSym = digits.at(0);
        char otherStartSym = other.digits.at(0);
        bool thisIsNegative = thisStartSym == '-';
        bool otherIsNegative = otherStartSym == '-';

        if ((thisIsNegative && !otherIsNegative && this->digits.substr(1) == other.digits) ||
                (!thisIsNegative && !otherIsNegative && this->digits == other.digits)) {
            return BigInteger("0");
        }

        // - a - (-b) = -a + b
        if (thisIsNegative && !otherIsNegative) {

        }

        // a - (-b) = a + b
        if (!thisIsNegative && otherIsNegative) {
            BigInteger b(other.digits.substr(1));
            return BigInteger((*this + b).toString());
        }

        // algorithm to know which of two string numbers is larger
        // check lenght first
        // if length is equal, then check the highest magnitude digit (furthest to the left)
        // the number with the larger such digit is bigger than the other
    }

    friend std::ostream& operator<<(std::ostream& os, BigInteger& bsi) {
        os << bsi.toString();
        return os;
    }
};