#include "shortest_path.h"

#include <climits>
#include <map>
#include <vector>

#include "common.h"
#include "common/graph.h"

int main() {
  for (int t = 0; t < 25; ++t) {
    int node_num = common::randint(0, 40);
    Graph<true, unsigned> g(node_num);
    std::size_t edge_num = 0;
    for (int i = 0; i < node_num; ++i) {
      for (int j = 0; j < node_num; ++j) {
        if (common::randint(0, 3) != 0) continue;
        g.add_edge(i, j, common::randint(0, 40));
        ++edge_num;
        if (common::randint(0, 3) != 0) continue;
        g.add_edge(i, j, common::randint(0, 40));
        ++edge_num;
      }
    }
    MY_ASSERT(edge_num == g.E());

    std::vector<std::vector<unsigned>> dist_d(
        g.V(), std::vector<unsigned>(g.V(), UINT_MAX));
    std::vector<std::vector<std::size_t>> next_d(
        g.V(), std::vector<std::size_t>(g.V(), SIZE_MAX));
    for (std::size_t source = 0; source < g.V(); ++source) {
      next_d[source][source] = source;
      std::map<std::size_t, unsigned> dist_m_d;
      std::map<size_t, size_t> prev_m_d;
      std::tie(dist_m_d, prev_m_d) = dijkstra(g, source);
      for (auto p : dist_m_d) {
        dist_d[source][p.first] = p.second;
      }
    }

    std::vector<std::vector<unsigned>> dist_f;
    std::vector<std::vector<std::size_t>> next_f;
    std::tie(dist_f, next_f) = flyod_warshall(g, UINT_MAX);

    for (int i = 0; i < g.V(); ++i) {
      for (int j = 0; j < g.V(); ++j) {
        MY_ASSERT(dist_d[i][j] == dist_f[i][j]);
      }
    }
  }

  // ===

  for (int t = 0; t < 25; ++t) {
    int node_num = common::randint(0, 40);
    Graph<false, unsigned> g(node_num);
    std::size_t edge_num = 0;
    for (int i = 0; i < node_num; ++i) {
      for (int j = 0; j < node_num; ++j) {
        if (common::randint(0, 3) != 0) continue;
        g.add_edge(i, j, common::randint(0, 40));
        ++edge_num;
        if (common::randint(0, 3) != 0) continue;
        g.add_edge(i, j, common::randint(0, 40));
        ++edge_num;
      }
    }
    MY_ASSERT(edge_num == g.E());

    std::vector<std::vector<unsigned>> dist_d(
        g.V(), std::vector<unsigned>(g.V(), UINT_MAX));
    std::vector<std::vector<std::size_t>> next_d(
        g.V(), std::vector<std::size_t>(g.V(), SIZE_MAX));
    for (std::size_t source = 0; source < g.V(); ++source) {
      next_d[source][source] = source;
      std::map<std::size_t, unsigned> dist_m_d;
      std::map<size_t, size_t> prev_m_d;
      std::tie(dist_m_d, prev_m_d) = dijkstra(g, source);
      for (auto p : dist_m_d) {
        dist_d[source][p.first] = p.second;
      }
    }

    std::vector<std::vector<unsigned>> dist_f;
    std::vector<std::vector<std::size_t>> next_f;
    std::tie(dist_f, next_f) = flyod_warshall(g, UINT_MAX);

    for (int i = 0; i < g.V(); ++i) {
      for (int j = 0; j < g.V(); ++j) {
        MY_ASSERT(dist_d[i][j] == dist_f[i][j]);
      }
    }
  }
}
