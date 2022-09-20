#ifndef UNTITLED26_INTEGERRANGE_H
#define UNTITLED26_INTEGERRANGE_H

#include <iterator>

struct IntegerIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int;
    using reference = int;

public:
    int value{};
    int step{};

public:
    constexpr IntegerIterator () = default;
    constexpr IntegerIterator (int value, int step) : value(value), step(step) {}
    constexpr IntegerIterator& operator ++ () {
        value += step;
        return *this;
    }
    constexpr IntegerIterator operator ++ (int)  {
        IntegerIterator result(*this);
        ++(*this);
        return result;
    }
    constexpr IntegerIterator& operator -- () {
        value -= step;
        return *this;
    }
    constexpr IntegerIterator operator -- (int) {
        IntegerIterator result(*this);
        --(*this);
        return result;
    }
    constexpr IntegerIterator operator + (int n) const {
        return IntegerIterator(value + n * step, step);
    }
    constexpr IntegerIterator operator - (int n) const {
        return IntegerIterator(value - n * step, step);
    }
    constexpr int operator [] (int n) const {
        return value + n * step;
    }
    constexpr bool operator == (const IntegerIterator& other) const  {
        return value == other.value;
    }
    constexpr bool operator != (const IntegerIterator& other) const {
        return !(*this == other);
    }
    constexpr bool operator < (const IntegerIterator& other) const {
        return value < other.value;
    }
    constexpr bool operator > (const IntegerIterator& other) const {
        return value > other.value;
    }
    constexpr bool operator <= (const IntegerIterator& other) const {
        return value <= other.value;
    }
    constexpr bool operator >= (const IntegerIterator& other) const {
        return value >= other.value;
    }
    constexpr int operator - (const IntegerIterator& other) const {
        return (value - other.value) / step;
    }
    constexpr IntegerIterator& operator += (int n) {
        value += n * step;
        return *this;
    }
    constexpr IntegerIterator& operator -= (int n) {
        value -= n * step;
        return *this;
    }
    constexpr int operator * () const {
        return value;
    }
    constexpr int operator -> () const {
        return value;
    }
};

constexpr IntegerIterator operator + (int n, const IntegerIterator& it) {
    return it + n;
}

//static_assert(std::random_access_iterator<IntegerIterator>);

struct IntegerRange {
private:
    int start;
    int last;
    int step = 1;

public:
    constexpr IntegerRange (int start, int last) : start(start), last(last) {}
    [[nodiscard]] constexpr IntegerIterator begin () const {
        return { start, step };
    }
    [[nodiscard]] constexpr IntegerIterator end () const {
        return { last, step };
    }
    [[nodiscard]] constexpr IntegerIterator cbegin () const {
        return begin();
    }
    [[nodiscard]] constexpr IntegerIterator cend () const {
        return end();
    }
    [[nodiscard]] constexpr std::size_t size () const {
        return (last - start) / step + 1;
    }
};


#endif //UNTITLED26_INTEGERRANGE_H
