#ifndef __IP_FILTER_H_INIGFE8BSKGV__
#define __IP_FILTER_H_INIGFE8BSKGV__

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <sstream>
#include <vector>

#include <asio/ip/address_v4.hpp>

namespace ip_filter {

using address_t = asio::ip::address_v4;
using address_list = std::vector<address_t>;

namespace address {

inline auto from_string(const std::string &address) noexcept
    -> ip_filter::address_t {
  return asio::ip::make_address_v4(address);
}

inline auto to_string(const address_t &address) noexcept -> std::string {
  return address.to_string();
}

}  // namespace address

const auto less = [](const address_t &lhs, const address_t &rhs) -> bool {
  return lhs < rhs;
};

const auto greater = [](const address_t &lhs, const address_t &rhs) -> bool {
  return lhs > rhs;
};

template <typename Container, typename Comp>
void sort(Container &&container, Comp &&comparator) {
  std::sort(std::begin(container), std::end(container), comparator);
}

template <typename Container, typename UnaryPredicate>
auto filter_if(const Container &container, UnaryPredicate &&pred) -> Container {
  Container result{};
  std::copy_if(std::begin(container), std::end(container),
               std::back_inserter(result), pred);
  return result;
}

}  // namespace ip_filter

#endif  // __IP_FILTER_H_INIGFE8BSKGV__
