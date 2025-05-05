#ifndef ITERATOR_H
#define ITERATOR_H


template <typename T>
class Iterator {
    T* iterator_;

public:
    explicit Iterator(T* iterator_to_save) { iterator_ = iterator_to_save; }

    ~Iterator() = default;

    const T* base() {
        return iterator_;
    }  // return a pointer that has address iterator points to

    T& operator*() {
        return *iterator_;
    }  /* overload the operator * which returns a value of pointer by reference
            (we can change the value that iterator points + we don't make the copy) */

    T* operator->() {
        return iterator_;
    }  // return the pointer that contains address

    Iterator& operator++() {
        ++iterator_;
        return *this;
    }  // returns reference to existing iterator(if needed)

    Iterator operator++(int) {
        return Iterator(iterator_++);
    }  // returning the copy of iterator(if needed), but also changes the original one(while passing);

    Iterator& operator--() {
        --iterator_;
        return *this;
    }  // returns reference to existing iterator(if needed)

    Iterator operator--(int) {
        return (iterator_--);
    }  // returning the copy of iterator(if needed), but also changes the original one(while passing);

    Iterator operator+(int t) const {
        return Iterator(iterator_ + t);
    }  // returns a copy of iterator

    Iterator operator-(int t) const {
        return Iterator(iterator_ - t);
    }  // returns a copy of iterator

    Iterator& operator+=(int t) {
        iterator_ += t;
        return *this;
    }

    Iterator& operator-=(int t) {
        iterator_ -= t;
        return *this;
    }

    T operator[](int n) { return iterator_[n]; }  // overloading [] operator

    bool operator==(const Iterator& other_iterator) {
        return this == other_iterator;
    }

    bool operator!=(const Iterator& other_iterator) {
        return this != other_iterator;
    }
};

// the same but vice versa actions(e.x: ++ turns to --)
template <typename T>
class ReverseIterator {
    T* reverse_iterator_;

public:
    explicit ReverseIterator(T* reverse_iterator_to_save) {
        reverse_iterator_ = reverse_iterator_to_save;
    }

    ~ReverseIterator() = default;

    const T* base() { return reverse_iterator_; }

    T& operator*() { return *reverse_iterator_; }

    T* operator->() { return reverse_iterator_; }

    ReverseIterator& operator++() {
        --reverse_iterator_;
        return *this;
    }

    ReverseIterator operator++(int) { return (reverse_iterator_--); }

    ReverseIterator& operator--() {
        ++reverse_iterator_;
        return *this;
    }

    ReverseIterator operator--(int) { return (reverse_iterator_++); }

    ReverseIterator operator+(int t) const {
        return ReverseIterator(reverse_iterator_ - t);
    }

    ReverseIterator operator-(int t) {
        return ReverseIterator(reverse_iterator_ + t);
    }

    ReverseIterator& operator+=(int t) {
        reverse_iterator_ -= t;
        return *this;
    }

    ReverseIterator& operator-=(int t) {
        reverse_iterator_ += t;
        return *this;
    }

    T operator[](int n) { return reverse_iterator_[n]; }

    bool operator==(const ReverseIterator& other_iterator) {
        return this == other_iterator;
    }

    bool operator!=(const ReverseIterator& other_iterator) {
        return this != other_iterator;
    }
};


#endif
