#include "mystring.h"

void *MyString::memcpy(void *s1, const void *s2, size_t n) {
    auto dest = static_cast<char*>(s1);
    auto src = static_cast<const char*>(s2);
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    return s1;
}

void *MyString::memmove(void *s1, const void *s2, size_t n) {
    auto dest = static_cast<char*>(s1);
    auto src = static_cast<const char*>(s2);
    if (dest <= src || dest >= src + n) {
        for (size_t i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            dest[i - 1] = src[i - 1];
        }
    }
    return s1;
}

char *MyString::strcpy(char *s1, const char *s2) {
    size_t i = 0;
    while ((s1[i] = s2[i]) != '\0') {
        i++;
    }
    return s1;
}

char *MyString::strncpy(char *s1, const char *s2, size_t n) {
    size_t i = 0;
    for (; i < n && s2[i] != '\0'; i++) {
        s1[i] = s2[i];
    }
    for (; i < n; i++) {
        s1[i] = '\0';
    }
    return s1;
}

char *MyString::strcat(char *s1, const char *s2) {
    size_t i = MyString::strlen(s1);
    MyString::strcpy(s1 + i, s2);
    return s1;
}

char *MyString::strncat(char *s1, const char *s2, size_t n) {
    size_t i = MyString::strlen(s1);
    size_t j = 0;
    for (; j < n && s2[j] != '\0'; j++) {
        s1[i + j] = s2[j];
    }
    s1[i + j] = '\0';
    return s1;
}

int MyString::memcmp(const void *s1, const void *s2, size_t n) {
    auto comp1 = static_cast<const unsigned char*>(s1);
    auto comp2 = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; i++) {
        if (comp1[i] < comp2[i]) {
            return -1;
        } else if (comp1[i] > comp2[i]) {
            return 1;
        }
    }
    return 0;
}

int MyString::strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return static_cast<int>(*s1) - static_cast<int>(*s2);
}

int MyString::strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i]) {
            return static_cast<int>(s1[i]) - static_cast<int>(s2[i]);
        }
    }
    return 0;
}

size_t MyString::strcspn(const char *s1, const char *s2) {
    size_t i = 0;
    while (s1[i] != '\0') {
        for (size_t j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
        i++;
    }
    return i;
}

void *MyString::memset(void *s, int c, size_t n) {
    auto p = static_cast<unsigned char*>(s);
    unsigned char u = static_cast<unsigned char>(c);
    for (size_t i = 0; i < n; i++) {
        p[i] = u;
    }
    return s;
}

size_t MyString::strlen(const char *s) {
    size_t length = 0;
    while (*s != '\0') {
        length++;
        s++;
    }
    return length;
}

MyString::MyString() {
    data = std::make_unique<char[]>(1);
    data[0] = '\0';
    sz = 1;
    cap = 1;
}

MyString::MyString(const char *str) {
    size_t len = MyString::strlen(str);
    sz = len + 1;
    cap = sz;
    data = std::make_unique<char[]>(sz);
    MyString::strcpy(data.get(), str);
}

MyString::MyString(const char *str, size_t n) {
    sz = n + 1;
    cap = sz;
    data = std::make_unique<char[]>(sz);
    MyString::strncpy(data.get(), str, n);
    data[n] = '\0';
}

MyString::MyString(size_t amount, char symbol) {
    sz = amount + 1;
    cap = sz;
    data = std::make_unique<char[]>(sz);
    MyString::memset(data.get(), symbol, amount);
    data[amount] = '\0';
}

char &MyString::operator[](size_t pos) {
    return data[pos];
}

const char &MyString::operator[](size_t pos) const {
    return data[pos];
}

MyString &MyString::operator=(const MyString &input) {
    if (this != &input) {
        sz = input.sz;
        cap = sz;
        data = std::make_unique<char[]>(sz);
        MyString::strcpy(data.get(), input.data.get());
    }
    return *this;
}

MyString &MyString::operator=(MyString &&input) noexcept {
    data = std::move(input.data);
    sz = input.sz;
    cap = input.cap;
    input.data = std::make_unique<char[]>(1);
    input.data[0] = '\0';
    input.sz = 1;
    input.cap = 1;
    return *this;
}

void MyString::resize(size_t newSize) {
    if (newSize + 1 <= sz) {
        sz = newSize + 1;
        data[newSize] = '\0';
    } else {
        reserve(newSize + 1);
        for (size_t i = sz - 1; i < newSize; i++) {
            data[i] = '\0';
        }
        sz = newSize + 1;
    }
}

void MyString::reserve(size_t newSize) {
    if (newSize <= cap) {
        return;
    }
    std::unique_ptr<char[]> newData = std::make_unique<char[]>(newSize);
    if (sz > 0) {
        MyString::memcpy(newData.get(), data.get(), sz);
    }
    data = std::move(newData);
    cap = newSize;
}

bool MyString::empty() {
    return sz <= 1;
}

size_t MyString::length() {
    return sz > 0 ? sz - 1 : 0;
}

size_t MyString::size() {
    return sz > 0 ? sz - 1 : 0;
}

MyString::iterator MyString::begin() {
    return data.get();
}

MyString::iterator MyString::end() {
    return data.get() + (sz > 0 ? sz - 1 : 0);
}
