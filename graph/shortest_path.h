// https://en.wikipedia.org/wiki/Shortest_path_problem

#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "common/graph.h"

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
template <bool IsDirected, typename WeightType>
std::pair<std::map<std::size_t, WeightType>, std::map<std::size_t, std::size_t>>
dijkstra(const Graph<IsDirected, WeightType>& g, std::size_t source) {
  std::map<std::size_t, WeightType> dist;   // <target, weight>
  std::map<std::size_t, std::size_t> prev;  // <target, previous step>
  if (source >= g.V()) return std::make_pair(dist, prev);

  dist[source] = 0;
  std::set<std::size_t> visited_vertex;
  for (std::size_t i = 0; i < g.V(); ++i) {
    visited_vertex.insert(i);
  }

  while (!visited_vertex.empty()) {
    std::unique_ptr<std::pair<std::size_t, WeightType>> min_uw_ptr;
    for (const auto dist_pair : dist) {
      if (visited_vertex.find(dist_pair.first) != visited_vertex.end()) {
        if (!min_uw_ptr || dist_pair.second < min_uw_ptr->second) {
          min_uw_ptr =
              std::make_unique<std::pair<std::size_t, WeightType>>(dist_pair);
        }
      }
    }
    if (!min_uw_ptr) break;
    std::size_t u = min_uw_ptr->first;
    visited_vertex.erase(u);
    const auto& edges = g.get_vertex_edge(u);
    for (const auto& edge : edges) {
      std::size_t v = edge.first;
      if (visited_vertex.find(v) == visited_vertex.end()) {
        continue;
      }
      const WeightType& w = edge.second;
      WeightType alt = dist.at(u) + w;
      if (dist.find(v) == dist.end() || alt < dist.at(v)) {
        dist[v] = alt;
        prev[v] = u;
      }
    }
  }
  return std::make_pair(std::move(dist), std::move(prev));
}

// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
template <bool IsDirected, typename WeightType>
std::pair<std::vector<std::vector<WeightType>>,
          std::vector<std::vector<std::size_t>>>
flyod_warshall(const Graph<IsDirected, WeightType>& g,
               const WeightType& maximum_weight) {
  std::vector<std::vector<WeightType>> dist(
      g.V(), std::vector<WeightType>(g.V(), maximum_weight));
  std::vector<std::vector<std::size_t>> next(
      g.V(), std::vector<std::size_t>(g.V(), SIZE_MAX));
  const auto all_edges = g.get_all_edge();
  for (const auto& edge : all_edges) {
    std::size_t u = edge.first.first;
    std::size_t v = edge.first.second;
    dist[u][v] = std::min(dist[u][v], edge.second);
    next[u][v] = v;
    if (!IsDirected && u != v) {
      dist[v][u] = std::min(dist[v][u], edge.second);
      next[v][u] = u;
    }
  }
  for (std::size_t v = 0; v < g.V(); ++v) {
    dist[v][v] = 0;
    next[v][v] = v;
  }
  for (std::size_t k = 0; k < g.V(); ++k) {
    for (std::size_t i = 0; i < g.V(); ++i) {
      for (std::size_t j = 0; j < g.V(); ++j) {
        if (dist[i][k] == maximum_weight || dist[k][j] == maximum_weight) {
          continue;
        }
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
  return std::make_pair(std::move(dist), std::move(next));

  // https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Path_reconstruction
  // procedure Path(u, v)
  //     if next[u][v] = null then
  //     return []
  //     path = [u]
  //            while u != v
  //                u = next[u][v]
  //            path.append(u)
  //                return path
}
