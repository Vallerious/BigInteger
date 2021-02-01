#include <iostream> // For any standard library use <>, otherwise use ""

#include <stdio.h>
#include <math.h>
#include <cstring>
void testStaticVariables();
short charArrayToScalar(char* ca, size_t l);
void swap(void* x, void* y, size_t size);

// generic function to add two integers! Does not work with float/doubles!!!!
void* add(void* a, void* b, int size) {

}

// this will work for non-reference types as it uses memcmp
int count_occurences(void* needle, void* base, int arrSize, int elemSize) {
    int count = 0;

    for (int i = 0; i < arrSize; i++) {
        void* currentEl = (char*)base + (i * elemSize);

        if (memcmp(currentEl, needle, elemSize) == 0) {
            count += 1;
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    long long term = 0xFFF;
    const int l = 10;
    long long arr[l] = {64, 0xFF39, 3, 2, 64, 1, 2, 64, 99, 4};
    int count = count_occurences(&term, &arr, l, sizeof(long long));
    std::cout << "The count of elements equal to " << term << " is: " << count << std::endl;
    // 1. Using streams connected to the console
    std::cout << "Hello, world!" << std::endl;

    short x1 = 3;
    short y1 = 5;

    swap(&x1, &y1, (size_t)sizeof(short));

    std::cout << "x had the value 3, but now has the value: " << x1 << std::endl;
    std::cout << "y had the value 5, but now has the value: " << y1 << std::endl;

    // 2. Variables & Data types
    const int base = 2;
    const int bitsInChar = (int)sizeof(char) * 8;

    printf("char\n");
    printf("at most (signed) char can fit %d values and is %d bit. Min value is %d, max value is %d\n",
           (int)pow(base, bitsInChar), bitsInChar, (int)pow(-base, bitsInChar - 1),
           (int)pow(base, bitsInChar - 1) - 1);

    printf("The set of signed chars is:\n");

    char c = (char)(pow(-base, bitsInChar - 1));

    while (true) {
        printf("%d ", c);

        if (c == (char)(pow(base, bitsInChar - 1) - 1)) { break; }

        c++;
    }
    printf("\n");

    // Interesting experiment...casting valid char values with (char)
    char a = (char)(pow(base, bitsInChar - 1) - 2);
    char b = (char)(pow(base, bitsInChar - 1) - 1);

    a++;

    printf("a: %d, b: %d\n", a, b);

    if (a == (char)b) {
        printf("The values are equal\n");
    }
    // end of experiment: turns out that casting has higher precedence than addition/subtraction

    printf("at most (unsigned) char can fit %d values and is %d bit. Min value is %d, max value is %d\n",
           (int) pow(base, bitsInChar), bitsInChar, 0, (int)pow(base, bitsInChar) - 1);

    printf("short\n");

    const int bitsInShort = sizeof(short) * 8;
    const int totalValuesInShort = (int)pow(base, bitsInShort);

    printf("at most (signed) short can fit %d values and is %d bit. Min value is %d, max value is %d\n",
           totalValuesInShort, bitsInShort, (int)pow(-base, bitsInShort - 1),
           (int)pow(base, bitsInShort - 1) - 1);

    printf("at most (unsigned) short can fit %d values and is %d bit. Min value is %d, max value is %d\n",
           totalValuesInShort, bitsInShort, 0,
           (int)pow(base, bitsInShort) - 1);


    printf("int\n");
    unsigned char const bitsInInt = (unsigned char)sizeof(int) * 8;

    printf("at most (signed) int can fit %d values and is %d bit. Min value is %d, max value is %d\n",
           (int)pow(2, bitsInInt), bitsInInt, (int)pow(-2, bitsInInt - 1),
           (int)pow(2, bitsInInt - 1) - 1);

    printf("Note: int is a shorthand for signed long int\n");

    printf("at most (unsigned) int can fit %d values and is %d bit. Min value is %d, max value is %ld\n",
           (int)pow(2, 32), (int)sizeof(int) * 8, 0, (unsigned long int)pow(2, 32) - 1);

    // 3. Static variables - Act similarly to static fields in classes, but for functions

    for (int i = 0; i < 10; ++i) {
        // testStaticVariables();
    }

    printf("Let's test floating point numbers!\n");
    float x = 12345678910111213.0f;

    printf("%f\n", x);

    printf("It turns out that floats can represent big numbers, but not precisely.\n");



    char eightBitNumber[8] = {0,0,1,0,0,1,0,1};
    short number = charArrayToScalar(eightBitNumber, 8);

    printf("The decimal value of the binary number 00100101 is %d\n", number);

    unsigned char y = 255;
    short z = y;

    printf("What the hell would happen? -> %hu\n", z);

    // Floating point representation

    // 0|00000000|00000000000000000000000
    // sign bit|exponent|fraction part (xxxxxx)
    // Formula is: sign bit * 1.xxxxx * 2^exp-127

    int i = 37;
    float f = *(float*)&i;

    printf("%.15f\n", f);

    float t = 7.123f;
    short s = *(short*)&t;

    printf("%d\n", s);

    return 0;
}

short charArrayToScalar(char* charArray, size_t len) {
    const char b = 2;
    int idx = len - 1;
    short res = 0;

    while (idx >= 0) {
        if (charArray[idx] == 1) {
            res += (short)pow(b, idx);
        }

        idx--;
    }

    return (short)res;
}

void testStaticVariables() {
    static int x = 10;
    printf("Here we print a locally scoped variable %d\n", x++);
}


void swap(void* x, void* y, size_t size) {
    char buffer[size];

    memcpy(buffer, x, size);
    memcpy(x, y, size);
    memcpy(y, buffer, size);
}