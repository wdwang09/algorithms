#pragma once

#include <vector>

std::vector<std::vector<int>> get_leetcode_style_tree(int null_symbol) {
  const int null = null_symbol;
  std::vector<std::vector<int>> trees{
      {},
      {1},
      {3, 9, 20, null, null, 15, 7},
      {0, -10, 5, null, -3, null, 9},
      {-3, -10, 0, null, null, null, 5},
      {5, 2, 7, 1, 3, 6, 8, null, null, null, 4, null, null, null, 9},
      {4, 2, 6, 1, 3, 5, 7, null, null, null, null, null, null, null, 8},
      {91,  18, null, null, 3,    25,   27,   14, 2,    null, 32,   16, 79,
       100, 59, 68,   null, null, null, null, 99, null, 55,   null, 64},
      {107,  151,  104,  null, 65,   15,   195,  79,   41,  7,   80,   null,
       186,  129,  171,  18,   null, 174,  131,  87,   36,  164, null, 190,
       161,  172,  null, 147,  19,   null, 113,  null, 73,  40,  12,   112,
       null, null, null, 124,  46,   93,   null, 188,  102, 118, null, 106,
       193,  69,   114,  155,  null, null, 137,  72,   39,  77,  121},
      {145, null, 85, 187, null, null, 50, null, 70, 170, null, 134},
      {83,   null, 59,   null, 40,   38,   180,  108,  174,  3,    138,
       119,  161,  60,   188,  92,   101,  13,   147,  186,  47,   null,
       15,   null, null, 165,  null, 166,  137,  190,  null, null, 116,
       null, 157,  null, null, null, null, null, null, null, null, null,
       null, null, null, null, null, null, null, null, 135},
      {159,  186, 107,  149,  31,  null, null, null, 10, 12, null, 40,
       95,   119, 190,  48,   152, 94,   null, 130,  6,  50, null, 38,
       null, 140, null, null, 112, 167,  58,   200,  75, 2},
      {167,  87,   103, 142,  137,  104,  null, 22,   29,  119,  197, 172,
       null, 156,  195, 59,   147,  null, 133,  null, 182, 54,   15,  184,
       null, 82,   173, 101,  65,   null, 102,  145,  6,   null, 44,  66,
       null, null, 79,  null, null, null, 74,   130,  17,  null, 121, null,
       56,   186,  70,  null, null, 168,  108,  48,   43,  null, 127, 41},
      {56,   3,    153,  null, 144, null, 193,  120, null, 185,  52,
       null, null, 173,  115,  165, 180,  159,  200, 170,  197,  130,
       114,  12,   28,   null, 135, null, null, 72,  null, null, null,
       60,   192,  null, 163,  74,  8,    null, 93},
  };
  return trees;
}
