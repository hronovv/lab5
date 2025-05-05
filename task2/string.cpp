#include "string.h"


GoodString::GoodString() {
    info_ = nullptr;
    size_ = 0;
    capacity_ = 0;
} // default constructor

GoodString::GoodString(const GoodString &other_string) {
    if (capacity_ < other_string.size_) {
        reserve(other_string.size_);
    } // just in case
    for (int i = 0; i < other_string.size_; i++) {
        info_[i] = other_string.info_[i]; // replacing
    }
    size_ = other_string.size_; // new size
} // copy constructor

GoodString::GoodString(const char *other_string) {
    int new_size = 0;
    while (other_string[new_size++]); // while not '\0'
    reserve(new_size);

    for (size_t i = 0; i < new_size; i++) {
        info_[i] = other_string[i]; // replacing
    }

    info_[new_size] = '\0'; // to end the string
    size_ = new_size;
}; // constructor if passing c_string

GoodString::GoodString(std::initializer_list<char> list) : size_(list.size()) {
    capacity_ = size_;
    std::unique_ptr<char[], decltype(deleter)> tmp(new char[size_], deleter);
    auto list_iterator = list.begin();
    for (int i = 0; i < size_; ++i, ++list_iterator) {
        tmp[i] = *list_iterator;
    }
    tmp[size_] = '\0';
    info_ = std::move(tmp);
} // constructor for passing separate symbols ( {'a','2'})

GoodString::~GoodString() {
    size_ = 0;
    capacity_ = 0;
    //std::unique_ptr will destroy himself(smart pointer btw)
}

void GoodString::reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) { return; }
//      auto tmp=std::make_unique<char[]>(size); // std::make_unique doesn't support overloaded deleters
    std::unique_ptr<char[], decltype(deleter)> tmp(new char[new_capacity], deleter);
    for (int i = 0; i < size_; i++) {
        tmp[i] = info_[i];
    }
    info_ = std::move(
            tmp); // that's because std::unique_ptr doesn't support copy constructor (either std::move or reset).
    capacity_ = new_capacity;
}

void GoodString::resize(size_t new_size, char temp) {
    if (new_size > capacity_) {
        reserve(new_size);
    }
    for (size_t i = size_; i < new_size; i++) {
        info_[i] = temp;
    }
    for (size_t i = new_size; i < size_; i++) {
        info_[i] = '\0';
    } // just blocking(pointing the end of the string) by replacing with '\0'
    size_ = new_size;
}

size_t GoodString::strlen(const char *s) {
    size_t len = 0;
    while (s[len]) { // while not '\0'
        len++;
    }
    return len;
}

void *GoodString::memmove(void *s1, const void *s2, size_t n) { // safe for data
    char *cs1 = (char *) s1;
    const char *cs2 = (const char *) s2; // just making pointers char, cause they support arithmetic
    if (cs1 < cs2 || cs1 >= cs2 + n) { // if not crossing
        for (size_t i = 0; i < n; ++i) {
            cs1[i] = cs2[i];
        }
    } else {
        for (size_t i = n; i > 0; --i) {
            cs1[i - 1] = cs2[i - 1];
        } // copying from the end and preventing from unexpected delete
    }
    return s1;
}

void *GoodString::memcpy(void *s1, const void *s2, size_t n) {
    // expecting that blocks of memory are not crossing each other
    if (!s1 || (!s2 && n > 0)) {
        return nullptr; // UB protection
    }

    char *cs1 = static_cast<char *>(s1);
    const char *cs2 = static_cast<const char *>(s2);

    for (size_t i = 0; i < n; ++i) {
        cs1[i] = cs2[i];
    }

    return s1;
}

char *GoodString::strcpy(char *s1, const char *s2) {
    if (!s1 || !s2) {
        return nullptr; // UB protection
    }
    char *original_s1 = s1;
    while ((*s1++ = *s2++)); // copying
    return original_s1; // returning pointer that points at the beginning
}

char *GoodString::strncpy(char *s1, const char *s2, size_t n) {
    if (!s1 || !s2) {
        return nullptr; // UB protection
    }
    char *original_s1 = s1;
    while (n-- && (*s1++ = *s2++));
    if (n) {
        *s1 = '\0';
    } // cause n can be < strlen(s2)
    return original_s1; // returning pointer that points at the beginning
}


int GoodString::memcmp(const void *s1, const void *s2, size_t n) {
    const char *iterator1 = static_cast<const char *>(s1);
    const char *iterator2 = static_cast<const char *>(s2);

    while (n--) {
        if (*iterator1 != *iterator2) {
            return (*iterator1 > *iterator2) ? 1 : -1;
        }
        iterator1++;
        iterator2++;
    }

    return 0; // just universal comparing
}

int GoodString::strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) { // s1 != '\0'
        s1++;
        s2++;
    }

    return *s1 > *s2 ? 1 : *s1 < *s2 ? -1 : 0;
}

int GoodString::strncmp(const char *s1, const char *s2, size_t n) {
    while (*s1 && (*s1 == *s2) && n--) {
        s1++;
        s2++;
    }
    if (n == 0) {
        return 0;
    }
    return *s1 > *s2 ? 1 : *s1 < *s2 ? -1 : 0;
}

int GoodString::strcoll(const char *s1, const char *s2) {
    setlocale(LC_COLLATE, ""); // expecting for previous LOCAL initialization (otherwise → en_US.UTF-8)
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return *s1 > *s2 ? 1 : *s1 < *s2 ? -1 : 0;
}


char *GoodString::strcat(char *s1, const char *s2) { // expected, that strlen(s1+s2) <= size (still works however)
    if (!s1 || !s2) {
        return nullptr; // UB protection
    }

    size_t size1 = strlen(s1);
    size_t i = 0;

    while (s2[i]) {
        s1[size1 + i] = s2[i];
        ++i;
    }

    s1[size1 + i] = '\0';

    return s1;
}

char *GoodString::strncat(char *s1, const char *s2, size_t n) {
    if (!s1 || !s2) {
        return nullptr; // UB protection
    }

    size_t size1 = strlen(s1);
    size_t i = 0;

    while (i < n && s2[i]) {
        s1[size1 + i] = s2[i];
        ++i;
    }

    s1[size1 + i] = '\0';

    return s1;
}

char *GoodString::strerror(int errnum) {
    static char *error_messages[] = {
            "Success",
            "Operation not permitted",
            "No such file or directory",
            "No such process",
            "Interrupted system call",
            "I/O error",
            "No such device or address",
            "Argument list too long",
            "Exec format error",
            "Bad file descriptor",
            "No child processes",
            "Resource temporarily unavailable",
            "Not enough memory",
            "Permission denied",
            "Bad address",
            "Device or resource busy",
            "File exists",
            "Invalid argument",
            "Unknown error"
    };

    size_t num_errors = sizeof(error_messages) / sizeof(error_messages[0]);
    if (errnum >= 0 && errnum < (int) num_errors) {
        return error_messages[errnum];
    }
    return "Unknown error";
}

void *GoodString::memset(void *s, int c, size_t n) {
    unsigned char *cs = (unsigned char *) s;
    for (size_t i = 0; i < n; i++)
        cs[i] = (unsigned char) c;
    return s;
} // filling n elements by char interpretation of c

char *GoodString::strtok(char *s1, const char *s2) {
    static char *last = nullptr;
    if (!s2) {
        return nullptr;
    }

    if (s1) {
        last = s1;
    }

    if (!last || !*last) {
        return nullptr;
    }

    while (*last && strchr(s2, *last)) {
        last++;
    }


    if (!*last) {
        return nullptr;
    }

    char *token_start = last;

    while (*last && !strchr(s2, *last))
        last++;

    if (*last) {
        *last = '\0';
        last++;
    } else {
        last = nullptr;
    }

    return token_start;
}

char *GoodString::strchr(const char *str, int c) { // finds symbol in string and returns a pointer to this symbol
    while (true) {
        if (*str == (char) c) {
            return (char *) str;
        }
        if (!*str) {
            return nullptr;
        }
        ++str;
    }
}

char *GoodString::strxfrm(char *s1, const char *s2, size_t n) { //expected local
    setlocale(LC_COLLATE, "");
    return strncpy(s1, s2, n);
}

char &GoodString::operator[](size_t n) {
    return info_[n];
} // overloading

GoodString &GoodString::operator=(const char *other_string) {
    if (info_.get() == other_string)
        return *this;
    size_t new_size = strlen(other_string);
    reserve(new_size);
    for (size_t i = 0; i <= new_size; i++) {
        info_[i] = other_string[i];
    }
    info_[new_size] = '\0';
    size_ = new_size;
    return *this;
} //move assignment operator if c_str

GoodString &GoodString::operator=(const GoodString &other_string) {
    if (this != &other_string) {
        size_ = other_string.size_;
        std::unique_ptr<char[], decltype(deleter)> tmp(new char[size_], deleter);
        strcpy(info_.get(), other_string.info_.get());
        info_ = std::move(tmp);
    }
    return *this;
} //move assignment operator for GoodString itself

// below functions, that are identical with vector's ones

bool GoodString::empty() {
    return size_ == 0;
}

void GoodString::clear() {
    resize(0);
}

size_t GoodString::size() const {
    return size_;
}

size_t GoodString::capacity() const {
    return capacity_;
}

char &GoodString::front() {
    return info_[0];
}

char &GoodString::back() {
    return info_[size_ - 1];
}

char &GoodString::at(size_t i) {
    if (i < size_) {
        return info_[i];
    } else {
        throw std::out_of_range("Index is out of range");
    }
}

char *GoodString::data() {
    return info_.get();
}

GoodString::basic_iterator GoodString::begin() {
    return basic_iterator(info_.get());
}

GoodString::basic_iterator GoodString::end() {
    return basic_iterator(info_.get() + size_);
}

GoodString::reverse_iterator GoodString::rbegin() {
    return reverse_iterator(info_.get() + size_);
}

GoodString::reverse_iterator GoodString::rend() {
    return reverse_iterator(info_.get());
}

GoodString::const_iterator GoodString::cbegin() {
    return const_iterator(info_.get());
}

GoodString::const_iterator GoodString::cend() {
    return const_iterator(info_.get() + size_);
}

void GoodString::swap(GoodString &other_string) {
    std::swap(other_string.size_, size_);
    std::swap(other_string.capacity_, capacity_);
    std::swap(other_string.info_, info_);
}

void GoodString::push_back(char c) {
    reserve(size_ + 2);
    info_[size_] = c;
    size_++;
    info_[size_] = '\0';
}

void GoodString::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("GoodString::pop_back: Attempt of deleting from empty string");
    }
    size_--;
    info_[size_] = '\0';
}


void GoodString::insert(const_iterator pos_, const char &tmp) {
    size_t pos = (pos_).base() - info_.get();
    reserve(size_ + 1);
    for (size_t i = size_; i > pos; i--) {
        info_[i] = info_[i - 1];
    }

    info_[pos] = tmp;
    size_++;
}

void GoodString::insert(const_iterator pos_, const char &&tmp) {
    size_t pos = (pos_).base() - info_.get();
    reserve(size_ + 1);
    for (size_t i = size_; i > pos; i--) {
        info_[i] = info_[i - 1];
    }

    info_[pos] = tmp;
    size_++;
}

void GoodString::erase(basic_iterator pos) {
    erase(pos, pos + 1);
}

void GoodString::erase(basic_iterator start, basic_iterator end) {
    size_t i = start.base() - info_.get();
    size_t j = end.base() - info_.get();
    if (i >= size_ || j > size_ || i >= j) {
        throw std::out_of_range("GoodString::erase: incorrect range");
    }
    for (size_t it = i; it < size_ - (j - i); it++) {
        info_[it] = info_[it + (j - i)];
    }
    size_ -= (j - i);
}

void GoodString::assign(size_t new_size, char c) {
    clear();
    resize(new_size, c);
}

void GoodString::assign(const_iterator start, const_iterator end) {
    clear();
    size_t size = end.base() - start.base();
    resize(size);
    for (size_t i = 0; i < size; i++) {
        info_[i] = *(start + i);
    }
}

void GoodString::emplace_back(char &&ch) {
    push_back(std::move(ch));
}

void GoodString::emplace(const_iterator pos, char &&ch) {
    insert(pos, std::move(ch));
}
