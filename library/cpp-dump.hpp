#include "./cpp-dump/cpp-dump.hpp"

namespace cp = cpp_dump;

#ifndef ONLINE_JUDGE
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif

void init_cpp_dump() {
  // ログのラベルを行番号にする
  CPP_DUMP_SET_OPTION(log_label_func, cp::log_label::filename());

  // 記号に色を付ける
  CPP_DUMP_SET_OPTION(es_value,
                      (cp::types::es_value_t{
                          "\x1b[02m",       // log: 灰色
                          "\x1b[34m",       // expression: 青
                          "\x1b[38;5;39m",  // reserved: 明るい青
                          "\x1b[38;5;150m", // number: 明るい緑
                          "\x1b[38;5;172m", // character: オレンジ
                          "\x1b[38;5;220m", // escaped_char: 明るいオレンジ
                          "\x1b[02m",       // op: 灰色
                          "\x1b[32m",       // identifier:  緑
                          "\x1b[96m",       // member: 明るいシアン
                          "\x1b[31m",       // unsupported: 赤
                          {
                              "\x1b[33m", // bracket_by_depth[0]: 黄色
                              "\x1b[35m", // bracket_by_depth[1]: マゼンタ
                              "\x1b[36m", // bracket_by_depth[2]: シアン
                          },
                          "\x1b[02m", // class_op: 灰色
                          "\x1b[02m", // member_op: 灰色
                          "",         // number_op: デフォルト
                      }));
  CPP_DUMP_SET_OPTION(detailed_class_es, true);
  CPP_DUMP_SET_OPTION(detailed_member_es, true);
  CPP_DUMP_SET_OPTION(detailed_number_es, true);
  CPP_DUMP_SET_OPTION(es_style, cp::types::es_style_t::by_syntax);
}
