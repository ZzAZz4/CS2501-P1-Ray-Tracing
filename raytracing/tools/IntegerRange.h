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
    constexpr IntegerIterator() = default;
    constexpr IntegerIterator(int value, int step) : value(value), step(step) {}
    constexpr auto operator++() -> IntegerIterator& {
        value += step;
        return *this;
    }
    constexpr auto operator++(int) -> IntegerIterator {
        IntegerIterator result(*this);
        ++(*this);
        return result;
    }
    constexpr auto operator--() -> IntegerIterator& {
        value -= step;
        return *this;
    }
    constexpr auto operator--(int) -> IntegerIterator {
        IntegerIterator result(*this);
        --(*this);
        return result;
    }
    constexpr auto operator+(int n) const -> IntegerIterator {
        return IntegerIterator(value + n * step, step);
    }
    constexpr auto operator-(int n) const -> IntegerIterator {
        return IntegerIterator(value - n * step, step);
    }
    constexpr auto operator[](int n) const -> int {
        return value + n * step;
    }
    constexpr auto operator==(const IntegerIterator& other) const -> bool {
        return value == other.value;
    }
    constexpr auto operator!=(const IntegerIterator& other) const -> bool {
        return !(*this == other);
    }
    constexpr auto operator<(const IntegerIterator& other) const -> bool {
        return value < other.value;
    }
    constexpr auto operator>(const IntegerIterator& other) const -> bool {
        return value > other.value;
    }
    constexpr auto operator<=(const IntegerIterator& other) const -> bool {
        return value <= other.value;
    }
    constexpr auto operator>=(const IntegerIterator& other) const -> bool {
        return value >= other.value;
    }
    constexpr auto operator-(const IntegerIterator& other) const -> int {
        return (value - other.value) / step;
    }
    constexpr auto operator+=(int n) -> IntegerIterator& {
        value += n * step;
        return *this;
    }
    constexpr auto operator-=(int n) -> IntegerIterator& {
        value -= n * step;
        return *this;
    }
    constexpr auto operator*() const -> int {
        return value;
    }
    constexpr auto operator->() const -> int {
        return value;
    }
};
constexpr auto operator+(int n, const IntegerIterator& it) -> IntegerIterator {
    return it + n;
}

//static_assert(std::random_access_iterator<IntegerIterator>);

struct IntegerRange {
private:
    int start;
    int last;
    int step = 1;

public:
    constexpr IntegerRange(int start, int last) : start(start), last(last) {}
    [[nodiscard]] constexpr auto begin() const -> IntegerIterator {
        return {start, step};
    }
    [[nodiscard]] constexpr auto end() const -> IntegerIterator {
        return {last, step};
    }
    [[nodiscard]] constexpr auto cbegin() const -> IntegerIterator {
        return begin();
    }
    [[nodiscard]] constexpr auto cend() const -> IntegerIterator {
        return end();
    }
    [[nodiscard]] constexpr auto size() const -> int {
        return (last - start) / step + 1;
    }
};


#endif //UNTITLED26_INTEGERRANGE_H
