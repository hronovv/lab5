#ifndef TASK2_STRING_H
#define TASK2_STRING_H
#include <memory>
#include <initializer_list>
#include "iterator.h"
#include <iostream>
using namespace std;


/*weak_ptr, shared_ptr, unique_ptr, auto_ptr(deprecated) → no need for multi addressing,
've chosen unique_ptr(possible to use std::move, replace). */


auto deleter = [](char* pointer){
    delete pointer;
    cout << "My own destructor works, because now it has been called!";
}; // just for a practical experience, overloaded std::unique_ptr destructor.

class GoodString {

    using basic_iterator = Iterator<char>;
    using reverse_iterator = ReverseIterator<char>;
    using const_iterator = Iterator<const char>;

public:

    GoodString();
    GoodString(const GoodString &other_string);
    GoodString(const char* other_string);
    GoodString(std::initializer_list<char> list);
    ~GoodString();

    void reserve(size_t new_capacity_);
    void resize(size_t new_size, char temp = char());
    bool empty();
    void clear();
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;
    char& front();
    char& back();
    char& at(size_t i);
    char* data();
    basic_iterator begin();
    basic_iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_iterator cbegin();
    const_iterator cend();
    void swap(GoodString &other_string);
    void push_back(char c);
    void pop_back();
    void insert(const_iterator pos, const char & tmp);
    void insert(const_iterator pos_, const char && tmp);
    void erase(basic_iterator start, basic_iterator end);
    void erase(basic_iterator pos);
    void assign(size_t new_size, char c);
    void assign(const_iterator start, const_iterator end);
    void emplace_back(char&& ch);
    void emplace(const_iterator pos, char&& ch);

    size_t strlen(const char* s);
    void* memmove(void* s1, const void* s2, size_t n);
    void* memcpy(void* s1, const void* s2, size_t n);
    char* strcpy(char* s1, const char* s2);
    char* strncpy(char* s1, const char* s2, size_t n);
    int memcmp(const void* s1, const void* s2, size_t n);
    int strcmp(const char* s1, const char* s2);
    int strncmp(const char* s1, const char* s2, size_t n);
    int strcoll(const char* s1, const char* s2);
    char* strcat(char* s1, const char* s2);
    char* strncat(char* s1, const char* s2, size_t n);
    char* strerror(int errnum);
    char* strtok(char* s1, const char* s2);
    void* memset(void *s, int c, size_t n);
    char* strxfrm(char *s1, const char *s2, size_t n);

    //operators
    char& operator[](size_t n);
    GoodString& operator=(const char* other_string);
    GoodString& operator=(const GoodString& other_string);


    //additional function
    char* strchr(const char *str, int c);
private:
    size_t size_, capacity_;
    unique_ptr<char[], decltype(deleter)> info_;
};


#endif //TASK2_STRING_H
