#pragma once

#include "std.hpp"
#include "types.hpp"

template <typename T>
struct nullable {
private:
  T value;
  bool exists;
public:
  nullable() : exists(false) {}
  nullable(nullptr_t) : exists(false) {}
  nullable(T value) : exists(true), value(value) {}
  nullable(const nullable<T>& other) : exists(other.exists), value(other.value) {}
  nullable(initializer_list<T> il) : exists(il.size() > 0), value(il) {}

  nullable& operator=(T&& rhs) {
    exists = true;
    value = move(rhs);
    return *this;
  }

  bool has_value() const {
    return exists;
  }

  explicit operator bool() const {
    return exists;
  }

  T& operator*() {
    return value;
  }

  const T& operator*() const {
    return value;
  }

  T* operator->() {
    return &value;
  }

  const T* operator->() const {
    return &value;
  }
};
