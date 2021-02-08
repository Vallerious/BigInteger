//
// Created by valeri on 8.02.21 г..
//
# pragma once

#include <cstdlib>

class PrependString {
private:
    char* buffer;
    int start;
public:
    PrependString(int capacity){
        buffer = (char*) malloc(sizeof(char) * (capacity + 1));
        buffer[capacity] = '\0';
        start = capacity - 1;
    }

    void prepend(char c) {
        buffer[start--] = c;
    }

    char* get_buffer() {
        return &buffer[++start];
    }

    ~PrependString() {
        free(buffer);
    }
};
