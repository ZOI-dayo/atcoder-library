#pragma once

#include "rbst-multiset.hpp"

template <typename T> struct RBSTSet : public RBSTMultiSet<T> {
public:
  inline RBSTSet() : RBSTMultiSet<T>() {}
  inline void insert(const T val) {
    if (contains(val))
      return;
    this->insert(val, lower_bound(val));
  }
};
