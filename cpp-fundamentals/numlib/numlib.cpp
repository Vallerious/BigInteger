#include <stdlib.h>
#include <math.h>
#include <string>
#include <limits>
#include <iostream>

const int BASE = 2;

// For now works with unsigned numbers
class Number {
private:
    const size_t DEFAULT_SIZE = 32;

    char* memory;
    size_t size;
    std::string decimalStr;

    void initializeValue(unsigned int value) {
        int start = this->size - 1;
        int end = 0;

        while (start >= end) {
            unsigned int mask = pow(BASE, start);
            unsigned int currentBit = value & mask;

            if (currentBit != 0) {
                this->memory[this->size - start - 1] = 1;
            }

            start--;
        }
    }
public:
    Number(unsigned int value) {
        this->size = DEFAULT_SIZE;
        this->memory = new char[size];
        this->initializeValue(value);
    }

    // maybe this wont be needed!
    unsigned int toDecimal() const {
        int start = this->size - 1;
        int end = 0;
        unsigned int value = 0;

        while (start >= end) {
            if ((int)this->memory[start] == 1) {
                value += pow(BASE, this->size - start - 1);
            }

            start -= 1;
        }

        return value;
    }

    const char* getBits() const {
        return this->memory;
    }

    size_t getSize() const {
        return this->size;
    }

    std::string toString() {
        if (this->decimalStr.empty()) {
            for (size_t idx = 0; idx < this->size; idx++) {
                this->decimalStr += std::to_string((unsigned int)this->memory[idx]);
            }
        }

        return this->decimalStr;
    }
};