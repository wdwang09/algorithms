// https://en.wikipedia.org/wiki/Minimum_spanning_tree

#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <set>
#include <vector>

#include "../disjoint_set/disjoint_set.h"
#include "common/graph.h"

// https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
template <typename WeightType>
Graph<false, WeightType> kruskal(const Graph<false, WeightType>& g) {
  Graph<false, WeightType> res(g.V());
  if (g.V() <= 1) return res;

  auto all_edges = g.get_all_edge();
  using PqPair = std::pair<WeightType, std::pair<std::size_t, std::size_t>>;
  std::priority_queue<PqPair, std::vector<PqPair>, std::greater<>> pq;
  for (const auto& edge : all_edges) {
    pq.emplace(edge.second, edge.first);
  }

  DisjointSet ds(g.V());
  while (!pq.empty()) {
    const auto& edge = pq.top();
    std::size_t u = edge.second.first;
    std::size_t v = edge.second.second;
    if (!ds.is_same_group(u, v)) {
      res.add_edge(u, v, edge.first);
      ds.merge(u, v);
      if (res.V() == res.E() + 1) {
        break;
      }
    }
    pq.pop();
  }
  return res;
}

// https://en.wikipedia.org/wiki/Prim%27s_algorithm
template <typename WeightType>
Graph<false, WeightType> prim(const Graph<false, WeightType>& g) {
  Graph<false, WeightType> res(g.V());
  if (g.V() <= 1) return res;

  std::set<std::size_t> remain_vertex_set;
  for (std::size_t i = 0; i < g.V(); ++i) {
    remain_vertex_set.insert(i);
  }

  using PqPair = std::pair<WeightType, std::pair<std::size_t, std::size_t>>;
  std::priority_queue<PqPair, std::vector<PqPair>, std::greater<>> pq;

  std::size_t current_vertex = 0;
  while (!remain_vertex_set.empty()) {
    if (remain_vertex_set.find(current_vertex) == remain_vertex_set.end()) {
      // current_vertex is invalid;
      current_vertex = *remain_vertex_set.cbegin();
    }
    remain_vertex_set.erase(current_vertex);
    const auto& edges = g.get_vertex_edge(current_vertex);
    for (const auto& edge : edges) {
      std::size_t v = edge.first;
      if (remain_vertex_set.find(v) == remain_vertex_set.end()) {
        continue;
      }
      const WeightType w = edge.second;
      pq.emplace(w, std::make_pair(current_vertex, v));
    }

    while (!pq.empty()) {
      const auto& pq_edge = pq.top();
      std::size_t u = pq_edge.second.first;
      std::size_t v = pq_edge.second.second;
      WeightType w = pq_edge.first;
      pq.pop();
      if (remain_vertex_set.find(v) != remain_vertex_set.end()) {
        res.add_edge(u, v, w);
        current_vertex = v;
        break;
      }
    }
  }
  return res;
}
