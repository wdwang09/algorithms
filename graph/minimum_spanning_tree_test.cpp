#include "minimum_spanning_tree.h"

#include "common.h"
#include "common/graph.h"

int main() {
  for (int t = 0; t < 100; ++t) {
    int node_num = common::randint(0, 40);
    Graph<false, int> g(node_num);
    std::size_t edge_num = 0;
    for (int i = 0; i < node_num; ++i) {
      for (int j = 0; j < node_num; ++j) {
        if (common::randint(0, 7) != 0) continue;
        g.add_edge(i, j, common::randint(-99, 99));
        ++edge_num;
      }
    }
    MY_ASSERT(edge_num == g.E());

    auto mst_k = kruskal(g);
    auto all_edge_k = mst_k.get_all_edge();

    auto mst_p = prim(g);
    auto all_edge_p = mst_p.get_all_edge();

    int weight_sum_k = 0;
    for (const auto& edge : all_edge_k) {
      weight_sum_k += edge.second;
    }
    int weight_sum_p = 0;
    for (const auto& edge : all_edge_p) {
      weight_sum_p += edge.second;
    }
    MY_ASSERT(mst_k.V() == 0 || mst_k.V() >= mst_k.E() + 1);
    MY_ASSERT(mst_p.V() == 0 || mst_p.V() >= mst_p.E() + 1);
    MY_ASSERT(weight_sum_k == weight_sum_p);
  }
}
