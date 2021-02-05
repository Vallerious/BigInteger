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
        bool AIsNegative = _isNeg(a);
        bool BIsNegative = _isNeg(b);

        // if x = 0 or y = 0 or (x = 0 and y = 0)
        if (zero == a) {
            return zero == b ? zero : b;
        } else if (zero == b) {
            return zero == a ? zero : a;
        }

        // _add a,b when |a| = |b| and a < 0 and b > 0 or a > 0 and b < 0
        if (((AIsNegative && !BIsNegative) || (!AIsNegative && BIsNegative)) &&
            _abs(a).compare(_abs(b)) == 0 && operation == BigInteger::OP::ADD) {
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
                return _subtract(_abs(b), _abs(a));
            }

            // x + y
            else if (!AIsNegative && !BIsNegative) {
                return _add(a, b);
            }
        } else if (operation == BigInteger::OP::SUB) {
            // -x - y
            if (AIsNegative && !BIsNegative) {
                return _negate(eval(_abs(a), _abs(b), BigInteger::OP::ADD));
            }
            // x - y
            else if (!AIsNegative && !BIsNegative) {
                return _subtract(a, b);
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

    bool _isNeg(std::string a) const {
        char firstCharInA = a.at(0);

        return firstCharInA == '-';
    }

    int _compareStrNumber(std::string a, std::string b) const {
        bool AIsNegative = _isNeg(a);
        bool BIsNegative = _isNeg(b);

        if (AIsNegative && !BIsNegative) {
            return -1;
        } else if (!AIsNegative && BIsNegative) {
            return 1;
        }

        if (AIsNegative && BIsNegative) {
            if (a.size() > b.size()) {
                return -1;
            } else if (a.size() < b.size()) {
                return 1;
            }

            return b.compare(a);
        }

        if (a.size() > b.size()) {
            return 1;
        } else if (b.size() > a.size()) {
            return -1;
        }

        return a.compare(b);
    }

    std::string _max(std::string a, std::string b) const {
        return _compareStrNumber(a, b) < 0 ? b : a;
    }

    std::string _add(std::string a, std::string b) const {
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

    std::string _subtract(std::string a, std::string b) const {
        // make so that a > b
        std::string subtractee = _max(a, b);
        std::string subtractor = a == subtractee ? b : a;

        int lenA = subtractee.size();
        int lenB = subtractor.size();
        int idxA = lenA - 1;
        int idxB = lenB - 1;
        std::string subResult;
        subResult.reserve(std::max(lenA, lenB) + 1);
        short carry = 0;

        while (idxA >= 0 || idxB >= 0) {
            short ac = idxA < 0 ? 0 : subtractee.at(idxA) - '0';
            short bc = idxB < 0 ? 0 : subtractor.at(idxB) - '0';

            short digitSub = ac - bc - carry;

            if (digitSub < 0) {
                carry = 1;
                digitSub += 10;
            } else {
                carry = 0;
            }

            if (!(idxA <= 0 && idxB <= 0 && digitSub == 0)) {
                subResult = std::to_string(digitSub) + subResult;
            }

            idxA -= 1;
            idxB -= 1;
        }

        return a < b ? _negate(subResult) : subResult;
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

    BigInteger max(BigInteger& b) const {
        return BigInteger(_max(digits, b.toString()));
    }

    int compare(const BigInteger& other) const {
        return _compareStrNumber(digits, other.digits);
    }

    BigInteger operator+(const BigInteger& other) const {
        return BigInteger(eval(digits, other.digits, BigInteger::OP::ADD));
    }

    BigInteger operator-(BigInteger& other) const {
        return BigInteger(eval(digits, other.digits, BigInteger::OP::SUB));
    }

    bool operator==(const BigInteger& other) const {
        return digits == other.digits;
    }

    bool operator==(const std::string& s) const {
        return digits == s;
    }

    friend std::ostream& operator<<(std::ostream& os, BigInteger& bsi) {
        os << bsi.toString();
        return os;
    }
};