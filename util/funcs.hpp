#pragma once

#include "macro.hpp"

template <typename T>
T sum(const vec<T>& v) {
    return accumulate(all(v), T(0));
}

template <typename T>
T max(const vec<T>& v) {
    return *max_element(all(v));
}

template <typename T>
T min(const vec<T>& v) {
    return *min_element(all(v));
}

template <typename T>
T gcd(const vec<T>& v) {
    return accumulate(all(v), T(0), [](T a, T b) { return gcd(a, b); });
}

template <typename T>
T lcm(const vec<T>& v) {
    return accumulate(all(v), T(1), [](T a, T b) { return a / gcd(a, b) * b; });
}

template <typename T>
bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T>
bool chmin(T& a, const T& b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
