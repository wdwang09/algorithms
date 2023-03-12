#include "optional.h"

#include <memory>
#include <string>

#include "common.h"

mine::optional<std::string> create(bool b, const std::string &s = "") {
  if (b) {
    return s;
  }
  return {};
}

auto create2(bool b, const std::string &s = "") {
  return b ? mine::optional<std::string>(s) : mine::nullopt;
}

int main() {
  MY_ASSERT(create(false).value_or("empty") == "empty");

  auto str = create2(true, "hi");
  MY_ASSERT(str.has_value());
  MY_ASSERT(str.value() == "hi");

  {
    std::shared_ptr<int> p1 = std::make_shared<int>(1);
    mine::optional<decltype(p1)> op1;
    MY_ASSERT(!op1.has_value());
    mine::optional<decltype(p1)> op2(p1);
    MY_ASSERT(op2.has_value());
    MY_ASSERT(*(op1.emplace(p1)) == 1);
    MY_ASSERT(op1.has_value());
  }

  {
    std::unique_ptr<int> u1 = std::make_unique<int>(1);
    std::unique_ptr<int> u2 = std::make_unique<int>(1);
    mine::optional<decltype(u1)> op1;
    MY_ASSERT(!op1.has_value());
    mine::optional<decltype(u1)> op2(std::move(u1));
    MY_ASSERT(op2.has_value());
    MY_ASSERT(*(op1.emplace(std::move(u2))) == 1);
    MY_ASSERT(op1.has_value());
  }
}
