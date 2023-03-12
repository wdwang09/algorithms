#include "binary_search.h"

#include <algorithm>
#include <vector>

#include "common.h"
#include "vector.h"

int main() {
  for (int i = 0; i < 200; ++i) {
    std::vector<int> v1 = random_int_vector();
    if (i == 0) {
      v1.clear();
    } else if (i == 1) {
      v1 = {1};
    }
    std::sort(v1.begin(), v1.end());
    for (int j = 0; j < v1.size(); ++j) {
      for (int k : {-1, 0, 1}) {
        bool is_found = std::binary_search(v1.begin(), v1.end(), v1[j] + k);
        auto my_it = binary_search(v1, v1[j] + k);
        if (is_found) {
          MY_ASSERT(v1.at(my_it) == v1[j] + k);
        } else {
          MY_ASSERT(my_it < 0);
        }
      }
    }
  }

  for (int i = 0; i < 200; ++i) {
    std::vector<int> v1 = random_int_vector();
    if (i == 0) {
      v1.clear();
    } else if (i == 1) {
      v1 = {1};
    }
    std::sort(v1.begin(), v1.end());
    for (int j = 0; j < v1.size(); ++j) {
      for (int k : {-1, 0, 1}) {
        bool is_found = std::binary_search(v1.begin(), v1.end(), v1[j] + k);
        auto my_it = lower_bound(v1, v1[j] + k);
        if (is_found) {
          MY_ASSERT(v1.at(my_it) == v1[j] + k);
          MY_ASSERT(my_it == 0 || v1.at(my_it - 1) < v1[j] + k);
        } else {
          MY_ASSERT(my_it < 0);
        }
      }
    }
  }

  for (int i = 0; i < 200; ++i) {
    std::vector<int> v1 = random_int_vector();
    if (i == 0) {
      v1.clear();
    } else if (i == 1) {
      v1 = {1};
    }
    std::sort(v1.begin(), v1.end());
    for (int j = 0; j < v1.size(); ++j) {
      for (int k : {-1, 0, 1}) {
        bool is_found = std::binary_search(v1.begin(), v1.end(), v1[j] + k);
        auto my_it = upper_bound(v1, v1[j] + k);
        if (is_found) {
          MY_ASSERT(v1.at(my_it) == v1[j] + k);
          MY_ASSERT(my_it + 1 == v1.size() || v1.at(my_it + 1) > v1[j] + k);
        } else {
          MY_ASSERT(my_it < 0);
        }
      }
    }
  }

  return 0;
}
