#pragma once

#include "alias.hpp"

// --- デバッグ ---
#ifndef ONLINE_JUDGE
// #define printd(x) cerr << #x << ": " << x << endl;
const string _TERM_ESC = "\033";
const string _TERM_BOLD = _TERM_ESC + "[1m";
const string _TERM_DECO_RESET = _TERM_ESC + "[0m";
const string _TERM_FORE_RED = _TERM_ESC + "[31m";
const string _TERM_FORE_RESET = _TERM_ESC + "[39m";
const string _TERM_BACK_RED = _TERM_ESC + "[41m";
const string _TERM_BACK_RESET = _TERM_ESC + "[49m";

#define line_debug() cerr << "line: " << __LINE__ << endl;
#define coutd(x) cerr << "[debug] " << x;
#define printd(x)                                                              \
  cerr << _TERM_BOLD << _TERM_BACK_RED << "[debug] " << #x << " = " << x       \
       << _TERM_BACK_RESET << _TERM_DECO_RESET << endl;

#else

#define line_debug() ;
#define coutd(x) ;
#define printd(x) ;

#endif
