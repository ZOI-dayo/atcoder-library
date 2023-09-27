#pragma once

#include <bits/stdc++.h>
using namespace std;

// ---------------
// ----- TOC -----
template <typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p);
template <typename T1, typename T2> istream &operator>>(istream &is, pair<T1, T2> &p);
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v);
template <typename T> ostream &operator<<(ostream &os, const vector<vector<T>> &v);
template <typename T> ostream &operator<<(ostream &os, const vector<vector<vector<T>>> &v);
template <typename T> istream &operator>>(istream &is, vector<T> &v);
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &mp);
template <typename T> ostream &operator<<(ostream &os, const set<T> &st);
template <typename T> ostream &operator<<(ostream &os, const multiset<T> &st);
template <typename T> ostream &operator<<(ostream &os, queue<T> q);
template <typename T> ostream &operator<<(ostream &os, deque<T> q);
template <typename T> ostream &operator<<(ostream &os, stack<T> st);
template <class T, class Container, class Compare> ostream &operator<<(ostream &os, priority_queue<T, Container, Compare> pq);
// --- END TOC ---
// ---------------

template <typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

template <typename T1, typename T2> istream &operator>>(istream &is, pair<T1, T2> &p) {
  is >> p.first >> p.second;
  return is;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "[";
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << (i + 1 != (int)v.size() ? ", " : "]");
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<vector<T>> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << endl;
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<vector<vector<T>>> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << "i = " << i << endl;
    os << v[i];
  }
  return os;
}

template <typename T> istream &operator>>(istream &is, vector<T> &v) {
  for (T &in : v) is >> in;
  return is;
}

template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &mp) {
  for (auto &[key, val] : mp) {
    os << key << ":" << val << " ";
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &st) {
  os << "{";
  auto itr = st.begin();
  for (int i = 0; i < (int)st.size(); i++) {
    os << *itr << (i + 1 != (int)st.size() ? ", " : "}");
    itr++;
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, const multiset<T> &st) {
  auto itr = st.begin();
  for (int i = 0; i < (int)st.size(); i++) {
    os << *itr << (i + 1 != (int)st.size() ? " " : "");
    itr++;
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, queue<T> q) {
  while (q.size()) {
    os << q.front() << " ";
    q.pop();
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, deque<T> q) {
  while (q.size()) {
    os << q.front() << " ";
    q.pop_front();
  }
  return os;
}

template <typename T> ostream &operator<<(ostream &os, stack<T> st) {
  while (st.size()) {
    os << st.top() << " ";
    st.pop();
  }
  return os;
}

template <class T, class Container, class Compare> ostream &operator<<(ostream &os, priority_queue<T, Container, Compare> pq) {
  while (pq.size()) {
    os << pq.top() << " ";
    pq.pop();
  }
  return os;
}
