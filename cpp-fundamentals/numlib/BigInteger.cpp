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
    enum OP { ADD, SUB, MUL, DEL };
    std::string zero = "0";

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

    std::string eval(std::string a, std::string b, BigInteger::OP operation) const {
        char firstCharInA = a.at(0);
        char firstCharInB = b.at(0);
        bool AIsNegative = firstCharInA == '-';
        bool BIsNegative = firstCharInB == '-';

        if (zero == a) {
            if (zero == b) {
                return zero;
            } else {
                return b;
            }
        } else if (zero == b) {
            if (zero == a) {
                return zero;
            } else {
                return a;
            }
        }

        // add a,b when |a| = |b| and a < 0 and b > 0 or a > 0 and b < 0
        if (((AIsNegative && !BIsNegative) || (!AIsNegative && BIsNegative)) &&
            _abs(a).compare(_abs(b)) == 0) {
            return "0";
        }

        if (operation == BigInteger::OP::ADD) {
            // -x + (-y) = -x - y
            if (AIsNegative && BIsNegative) {
                return _negate(eval(_abs(a), _abs(b), BigInteger::OP::ADD));
            }
            // x + (-y) = x - y
            else if (!AIsNegative && BIsNegative) {
                return eval(a, _abs(b), BigInteger::OP::SUB);
            }

            // -x + y = y - x
            else if (AIsNegative && !BIsNegative) {
                return eval(b, a, BigInteger::OP::SUB);
            }

            // x + y
            else if (!AIsNegative && !BIsNegative) {
                return add(a, b);
            }
        } else if (operation == BigInteger::OP::SUB) {
            // -x - y
            if (AIsNegative && !BIsNegative) {
                return _negate(eval(_abs(a), _abs(b), BigInteger::OP::ADD));
            }
            // x - y
            else if (!AIsNegative && !BIsNegative) {
                // subtract
            }

            // -x - (-y) = -x + y
            else if (AIsNegative && BIsNegative) {
                return eval(a, _abs(b), BigInteger::OP::ADD);
            }

            // x - (-y) = x + y
            else if (!AIsNegative && BIsNegative) {
                return eval(a, _abs(b), BigInteger::OP::ADD);
            }
        }

        return "";
    }

    std::string _negate(std::string a) const {
        if (a.at(0) == '-') {
            return a;
        }

        return "-" + a;
    }

    std::string _abs(std::string a) const {
        if (a.at(0) == '-') {
            return a.substr(1);
        }

        return a;
    }

    std::string add(std::string a, std::string b) const {
        int lenA = a.size();
        int lenB = b.size();
        int idxA = lenA - 1;
        int idxB = lenB - 1;
        std::string sumStr;
        sumStr.reserve(std::max(lenA, lenB) + 1);
        short carry = 0;

        while (idxA >= 0 || idxB >= 0) {
            short ac = idxA < 0 ? 0 : a.at(idxA) - '0';
            short bc = idxB < 0 ? 0 : b.at(idxB) - '0';

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

        return sumStr;
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
        return BigInteger(eval(digits, other.digits, BigInteger::OP::ADD));
    }

    BigInteger operator-(BigInteger& other) const {
        return BigInteger(eval(digits, other.digits, BigInteger::OP::SUB));
    }

    friend std::ostream& operator<<(std::ostream& os, BigInteger& bsi) {
        os << bsi.toString();
        return os;
    }
};