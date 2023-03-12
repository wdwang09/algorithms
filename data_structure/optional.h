#pragma once

#include <utility>

namespace mine {

// NOLINTBEGIN(google-explicit-constructor)

struct nullopt_t {};
constexpr nullopt_t nullopt;

template <class T>
class optional {
 private:
  T value_;
  bool is_with_value_ = false;

 public:
  optional() = default;
  optional(const nullopt_t n) {}

  optional(const optional<T>& other) {
    is_with_value_ = other.is_with_value_;
    if (is_with_value_) {
      value_ = other.value_;
    }
  }

  optional(optional<T>&& other) noexcept {
    is_with_value_ = other.is_with_value_;
    if (is_with_value_) {
      value_ = std::move(other.value_);
    }
  }

  optional(const T& value) {
    is_with_value_ = true;
    value_ = value;
  }

  optional(T&& value) {
    is_with_value_ = true;
    value_ = std::move(value);
  }

  const T& value() const { return value_; }

  T value_or(T&& value) const {
    if (is_with_value_) {
      return value_;
    } else {
      return value;
    }
  }

  bool has_value() const { return is_with_value_; }

  constexpr T& emplace(const T& value) {
    is_with_value_ = true;
    value_ = value;
    return value_;
  }

  constexpr T& emplace(T&& value) {
    is_with_value_ = true;
    value_ = std::move(value);
    return value_;
  }
};

// NOLINTEND(google-explicit-constructor)

}  // namespace mine
