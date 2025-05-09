#ifndef MYSTRING_H
#define MYSTRING_H

#include <memory>

class MyString {
private:
    std::unique_ptr<char[]> data;
    size_t sz = 0;
    size_t cap = 1;

    using iterator = char*;
    using const_iterator = const char*;

public:
    MyString();
    explicit MyString(const char *str);
    MyString(const MyString& str, size_t pos, size_t len);
    MyString(const char* str, size_t n);
    MyString(const MyString& other);
    MyString(size_t amount, char symbol);\
    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;
    MyString& operator=(const MyString& input);
    MyString& operator=(MyString &&input) noexcept;
    void resize(size_t newSize);
    void reserve(size_t size);
    bool empty();
    size_t length() const;
    size_t size() const;
    size_t capacity() const;
    iterator begin();
    iterator end();

    static void *memcpy(void *s1, const void *s2, size_t n);
    static void *memmove(void *s1, const void *s2, size_t n);
    static char *strcpy(char *s1, const char *s2);
    static char *strncpy(char *s1, const char *s2, size_t n);
    static char *strcat(char *s1, const char *s2);
    static char *strncat(char *s1, const char *s2, size_t n);
    static int memcmp(const void *s1, const void *s2, size_t n);
    static int strcmp(const char *s1, const char *s2);
    static int strncmp(const char *s1, const char *s2, size_t n);
    static size_t strcspn(const char *s1, const char *s2);
    static void *memset(void *s, int c, size_t n);
    static size_t strlen(const char *s);
    static char *strerror(int errnum);
    void throwError(int errnum) const;
};

#endif // MYSTRING_H
