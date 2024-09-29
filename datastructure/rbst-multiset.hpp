#pragma once

#include "rbst.hpp"

namespace zoi {
  namespace datastructure {

    template <typename T> struct RBSTMultiSet : public RBST<T> {
    private:
      using node_t = typename RBST<T>::node_t;

    public:
      inline RBSTMultiSet() : RBST<T>(0, [](T a, T b) { return a; }) {}

      inline size_t lower_bound(const node_t* const t, T val) const {
        if (!t) return 0;
        if (val <= this->val(t)) return lower_bound(t->lch, val);
        return this->size(t->lch) + 1 + lower_bound(t->rch, val);
      }

      inline size_t lower_bound(const T val) const {
        return lower_bound(this->root, val);
      }

      inline size_t upper_bound(const node_t* const t, const T val) const {
        if (!t) return 0;
        if (val < t->val) return upper_bound(t->lch, val);
        return this->size(t->lch) + 1 + upper_bound(t->rch, val);
      }

      inline size_t upper_bound(const T val) const {
        return upper_bound(this->root, val);
      }

      inline void insert(const T val) {
        this->insert_at(lower_bound(val), val);
      }

      inline size_t count(const T val) const {
        return upper_bound(val) - lower_bound(val);
      }

      inline bool contains(const T val) const {
        int idx = lower_bound(val);
        return idx < this->root->size && this->get_at(idx)->val == val;
      }

      inline void erase(const T val) {
        int idx = lower_bound(val);
        if (idx < this->root->size && this->get_at(idx)->val == val)
          this->erase_at(idx);
      }
    };

  } // namespace datastructure
} // namespace zoi
