#pragma once

#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

template <bool IsDirected, typename WeightType>
class Graph {
 public:
  explicit Graph(std::size_t vertex_num)
      : is_directed_(IsDirected), adjacency_list_(vertex_num), edge_num_(0) {}

  std::size_t V() const { return adjacency_list_.size(); }
  std::size_t E() const { return edge_num_; }

  bool add_edge(std::size_t u, std::size_t v, const WeightType& w) {
    if (u >= V() || v >= V()) return false;
    adjacency_list_.at(u).emplace(v, w);
    if (!is_directed_) {
      adjacency_list_.at(v).emplace(u, w);
    }
    ++edge_num_;
    return true;
  }

  // bool is_edge(std::size_t u, std::size_t v) const {
  //   if (u >= V() || v >= V()) return false;
  //   return adjacency_list_.at(u).find(v) != adjacency_list_.at(u).end();
  // }

  // WeightType get_weight(std::size_t u, std::size_t v) const {
  //   if (!is_edge(u, v)) {
  //     throw std::runtime_error("The edge doesn't exist.");
  //   }
  //   return adjacency_list_.at(u).find(v)->second;
  // }

  const std::multimap<std::size_t, WeightType>& get_vertex_edge(
      std::size_t u) const {
    return adjacency_list_.at(u);
  }

  std::multimap<std::pair<std::size_t, std::size_t>, WeightType> get_all_edge()
      const {
    std::multimap<std::pair<std::size_t, std::size_t>, WeightType> res;
    for (std::size_t u = 0; u < V(); ++u) {
      for (const auto& edge : adjacency_list_.at(u)) {
        std::size_t v = edge.first;
        WeightType w = edge.second;
        if (!is_directed_ && u > v) {
          continue;
        }
        res.emplace(std::pair<std::size_t, std::size_t>(u, v), w);
      }
    }
    return res;
  }

 private:
  const bool is_directed_;
  std::vector<std::multimap<std::size_t, WeightType>> adjacency_list_;
  std::size_t edge_num_ = 0;
};
