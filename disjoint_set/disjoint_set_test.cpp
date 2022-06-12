#include "disjoint_set.h"

#include "common.h"

int main() {
  DisjointSet ds(10);
  MY_ASSERT(!ds.is_same_group(0, 1));
  ds.merge(0, 1);
  MY_ASSERT(ds.is_same_group(0, 1));
  MY_ASSERT(!ds.is_same_group(0, 2));
  ds.merge(1, 2);
  MY_ASSERT(ds.is_same_group(0, 2));
  ds.merge(3, 4);
  ds.merge(3, 5);
  MY_ASSERT(!ds.is_same_group(2, 3));
  MY_ASSERT(ds.is_same_group(4, 5));
  ds.merge(1, 5);
  MY_ASSERT(ds.is_same_group(0, 4));
  return 0;
}
