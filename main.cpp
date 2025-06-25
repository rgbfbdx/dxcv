// MyString.h
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>

class MyString {
private:
    char* str;
    int length;

public:
    MyString();
    MyString(int size);
    MyString(const char* s);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    MyString operator+(const MyString& other) const;
    char& operator[](int index);

    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
    friend std::istream& operator>>(std::istream& is, MyString& s);
};

#endif

// MyString.cpp
#include "MyString.h"

MyString::MyString() : str(nullptr), length(0) {}

MyString::MyString(int size) : length(size) {
    str = new char[length + 1]{};
}

MyString::MyString(const char* s) {
    length = std::strlen(s);
    str = new char[length + 1];
    std::strcpy(str, s);
}

MyString::MyString(const MyString& other) : length(other.length) {
    str = new char[length + 1];
    std::strcpy(str, other.str);
}

MyString::MyString(MyString&& other) noexcept : str(other.str), length(other.length) {
    other.str = nullptr;
    other.length = 0;
}

MyString::~MyString() {
    delete[] str;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        std::strcpy(str, other.str);
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] str;
        str = other.str;
        length = other.length;
        other.str = nullptr;
        other.length = 0;
    }
    return *this;
}

MyString MyString::operator+(const MyString& other) const {
    MyString result(length + other.length);
    std::strcpy(result.str, str);
    std::strcat(result.str, other.str);
    return result;
}

char& MyString::operator[](int index) {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of range");
    return str[index];
}

std::ostream& operator<<(std::ostream& os, const MyString& s) {
    if (s.str)
        os << s.str;
    return os;
}

std::istream& operator>>(std::istream& is, MyString& s) {
    char buffer[1000];
    is >> buffer;
    delete[] s.str;
    s.length = std::strlen(buffer);
    s.str = new char[s.length + 1];
    std::strcpy(s.str, buffer);
    return is;
}
