#include "string.h"

String::String() : ptr(std::make_unique<char[]>(1)), sz(1), cp(1) {
    ptr[0] = '\0';
}

void *String::memcpy(void *s1, const void *s2, size_t n)
{
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }
    char *dest = static_cast<char *>(s1);
    const char *src = static_cast<const char *>(s2);

    for (size_t i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
    return s1;
}

void *String::memmove(void *s1, const void *s2, size_t n)
{
    auto aim = static_cast<char *>(s1);
    auto src = static_cast<const char *>(s2);

    if (aim < src) {
        for (size_t i = 0; i < n; ++i) {
            aim[i] = src[i];
        }
    } else if (aim > src) {
        for (size_t i = n; i > 0; --i) {
            aim[i - 1] = src[i - 1];
        }
    }

    return s1;
}

char *String::strcpy(char *s1, const char *s2)
{
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }
    size_t i = 0;
    while (s2[i] != '\0') {
        ++i;
    }
    memcpy(s1, s2, i);
    s1[i] = '\0';
    return s1;
}

char *String::strncpy(char *s1, const char *s2, size_t n)
{
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }

    size_t i = 0;
    while (i < n && s2[i] != '\0') {
        s1[i] = s2[i];
        ++i;
    }
    while (i < n) {
        s1[i] = '\0';
        ++i;
    }

    return s1;
}

char *String::strcat(char *s1, const char *s2)
{
    size_t i = 0, j = 0;
    while (s1[i] != '\0') {
        ++i;
    }
    while (s2[j] != '\0') {
        s1[i] = s2[j];
        ++i;
        ++j;
    }
    s1[i] = '\0';
    return s1;
}

char *String::strncat(char *s1, const char *s2, size_t n)
{
    char *temp = s1;
    while (*s1) {
        ++s1;
    }
    while (n-- && *s2) {
        *s1++ = *s2++;
    }
    *s1 = '\0';
    return temp;
}

int String::memcmp(const void *s1, const void *s2, size_t n)
{
    auto p1 = static_cast<const unsigned char *>(s1);
    auto p2 = static_cast<const unsigned char *>(s2);

    for (size_t i = 0; i < n; ++i) {
        if (p1[i] < p2[i]) {
            return -1;
        }
        if (p1[i] > p2[i]) {
            return 1;
        }
    }

    return 0;
}

int String::strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}

int String::strncmp(const char *s1, const char *s2, size_t n)
{
    while (--n && *s1 == *s2) {
        if (*s1 == '\0') {
            return 1;
        }
        s1++;
        s2++;
    }

    return (*s1 - *s2);
}

size_t String::strcspn(const char *s1, const char *s2)
{
    size_t count = 0;

    while (*s1 != '\0') {
        const char *p = s2;
        while (*p != '\0') {
            if (*s1 == *p) {
                return count;
            }
            ++p;
        }
        ++count;
        ++s1;
    }

    return count;
}

void *String::memset(void *s, int c, size_t n)
{
    unsigned char *p = static_cast<unsigned char *>(s);
    unsigned char uc = static_cast<unsigned char>(c);

    for (size_t i = 0; i < n; ++i) {
        p[i] = uc;
    }

    return s;
}

size_t String::strlen(const char *s)
{
    size_t length = 0;

    while (*s != '\0') {
        ++length;
        ++s;
    }

    return length;
}

String::String(const char *str)
{
    size_t mySize = strlen(str) + 1;
    ptr = std::make_unique<char[]>(mySize);
    sz = mySize;
    cp = mySize;
    memcpy(ptr.get(), str, strlen(str));
}

String::String(size_t amnt, char c)
    : ptr(std::make_unique<char[]>(amnt + 1))
    , sz(amnt + 1)
    , cp(amnt + 1)
{
    for (size_t i = 0; i < amnt; ++i) {
        ptr[i] = c;
    }
}

String::String(const String &other)
    : ptr(std::make_unique<char[]>(other.sz))
    , sz(other.sz)
    , cp(other.sz)
{
    strcpy(ptr.get(), other.ptr.get());
}

String::String(String &&other) noexcept
    : ptr(std::move(other.ptr))
    , sz(other.sz)
    , cp(other.sz)
{
    other.cp = 0;
    other.sz = 0;
    other.resize(0);
}

String &String::operator=(const String &other)
{
    if (&other != this) {
        ptr = std::make_unique<char[]>(other.sz);
        sz = other.sz;
        cp = other.cp;
        strcpy(ptr.get(), other.ptr.get());
    }

    return *this;
}

String &String::operator=(String &&other) noexcept
{
    ptr = std::move(other.ptr);
    sz = other.sz;
    cp = other.cp;

    other.cp = 0;
    other.sz = 0;
    other.resize(0);

    return *this;
}

void String::resize(size_t newSize)
{
    ++newSize;
    if (newSize <= sz) {
        sz = newSize;
        ptr[sz - 1] = '\0';
    } else {
        reserve(newSize);
        for (size_t i = sz; i < newSize; ++i) {
            ptr[i] = '\0';
        }
        sz = newSize;
    }
}

void String::reserve(size_t newSize)
{
    ++newSize;
    if (newSize <= cp) {
        return;
    }

    std::unique_ptr<char[]> newData = std::make_unique<char[]>(newSize);
    if (sz > 1) {
        memcpy(newData.get(), ptr.get(), sz);
    }
    ptr = std::move(newData);
    cp = newSize;
}

bool String::empty() const
{
    return sz <= 1;
}

size_t String::size() const
{
    if (sz == 0) {
        return 0;
    }
    return sz - 1;
}

size_t String::capacity() const
{
    return cp;
}

char &String::at(size_t pos)
{
    if (pos >= sz) {
        throw std::out_of_range("Index out of range");
    }
    return ptr[pos];
}

const char &String::at(size_t pos) const
{
    if (pos >= sz) {
        throw std::out_of_range("Index out of range");
    }
    return ptr[pos];
}

char &String::operator[](size_t pos)
{
    return ptr[pos];
}

const char &String::operator[](size_t pos) const
{
    return ptr[pos];
}

char &String::front()
{
    return ptr[0];
}

const char &String::front() const
{
    return ptr[0];
}

char &String::back()
{
    return ptr[sz - 2];
}

const char &String::back() const
{
    return ptr[sz - 2];
}

const char *String::c_str() const
{
    return ptr.get();
}

const char *String::data() const
{
    return ptr.get();
}

char *String::begin()
{
    return ptr.get();
}

const char *String::begin() const
{
    return ptr.get();
}

char *String::end()
{
    return ptr.get() + sz - 1;
}

const char *String::end() const
{
    return ptr.get() + sz - 1;
}

std::reverse_iterator<char *> String::rbegin()
{
    return std::reverse_iterator<char *>(end());
}

std::reverse_iterator<const char *> String::rbegin() const
{
    return std::reverse_iterator<const char *>(end());
}

std::reverse_iterator<char *> String::rend()
{
    return std::reverse_iterator<char *>(begin() - 1);
}

std::reverse_iterator<const char *> String::rend() const
{
    return std::reverse_iterator<const char *>(begin() - 1);
}

void String::clear()
{
    resize(0);
}

void String::erase(size_t pos, size_t len)
{
    len = std::min(len, sz - pos);
    memmove(ptr.get() + pos, ptr.get() + pos + len, sz - pos - len + 1);
    sz -= len;
}

void String::push_back(char c)
{
    if (sz + 1 >= cp) {
        reserve(cp == 0 ? 2 : cp * 2);
    }

    ptr[sz - 1] = c;
    ptr[sz] = '\0';
    ++sz;
}

void String::pop_back()
{
    if (sz > 1) {
        back() = '\0';
        --sz;
        return;
    }

    if (cp != 0) {
        front() = '\0';
    }
}

size_t String::copy(char *dest, size_t len, size_t pos) const
{
    if (pos > size()) {
        throw std::out_of_range("Position out of range");
    }

    size_t count = std::min(std::min(len, size() - pos), strlen(dest));
    memcpy(dest, ptr.get() + pos, count);
    return count;
}

void String::insert(size_t pos, const char *str)
{
    reserve(strlen(str) + size());

    memmove(ptr.get() + pos + strlen(str), ptr.get() + pos, sz - pos);
    memcpy(ptr.get() + pos, str, strlen(str));
    sz += strlen(str);
}

void String::insert(size_t pos, const String &str)
{
    insert(pos, str.data());
}

void String::insert(size_t pos, size_t n, char c)
{
    if (pos > sz) {
        throw std::out_of_range("Position out of range");
    }

    size_t newSize = sz + n;
    reserve(newSize);
    memmove(ptr.get() + pos + n, ptr.get() + pos, sz - pos + 1);
    memset(ptr.get() + pos, c, n);
    sz = newSize;
}

void String::append(const char *str)
{
    insert(sz - 1, str);
}

void String::append(const String &str)
{
    append(str.data());
}

void String::append(size_t n, char c)
{
    insert(sz - 1, n, c);
}

void String::replace(size_t pos, size_t len, const char *str)
{
    erase(pos, len);
    insert(pos, str);
}

void String::replace(size_t pos, size_t len, const String &str)
{
    replace(pos, len, str.data());
}

size_t String::find(const String &str, size_t pos) const
{
    return find(str.c_str(), pos);
}

size_t String::find(const char *str, size_t pos) const
{
    size_t len = strlen(str);
    if (len == 0) {
        return pos <= sz ? pos : -1;
    }
    if (pos >= sz || size() == 0) {
        return -1;
    }

    for (size_t i = pos; i + len <= sz; ++i) {
        bool found = true;
        for (size_t j = 0; j < len; ++j) {
            if (ptr[i + j] != str[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

size_t String::rfind(const char *str, size_t pos) const
{
    size_t len = strlen(str);
    if (len == 0) {
        return pos <= sz ? pos : -1;
    }
    if (pos >= sz) {
        pos = sz - 1;
    }
    if (size() == 0) {
        return -1;
    }

    for (size_t i = pos; i != -1; --i) {
        bool found = true;
        for (size_t j = 0; j < len; ++j) {
            if (i + j >= sz || ptr[i + j] != str[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

size_t String::rfind(const char *str) const
{
    return rfind(str, sz - 1);
}

size_t String::rfind(const String &str, size_t pos) const
{
    return rfind(str.c_str(), pos);
}

size_t String::rfind(const String &str) const
{
    return rfind(str.c_str());
}

int String::compare(const String &str) const
{
    return strcmp(ptr.get(), str.ptr.get());
}

String operator+(const String &left, const String &right)
{
    String result(left);
    result.append(right);
    return result;
}

String operator+(const String &left, char right)
{
    String result(left);
    result.push_back(right);
    return result;
}

String operator+(char left, const String &right)
{
    String result(1, left);
    result.append(right);
    return result;
}

bool operator==(const String &left, const String &right)
{
    return left.compare(right) == 0;
}

bool operator!=(const String &left, const String &right)
{
    return !(left == right);
}

bool operator<(const String &left, const String &right)
{
    return left.compare(right) < 0;
}

bool operator>(const String &left, const String &right)
{
    return right < left;
}

bool operator<=(const String &left, const String &right)
{
    return !(right < left);
}

bool operator>=(const String &left, const String &right)
{
    return !(left < right);
}
