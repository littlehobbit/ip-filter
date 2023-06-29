#ifndef __IP_FILTER_H_INIGFE8BSKGV__
#define __IP_FILTER_H_INIGFE8BSKGV__

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <sstream>
#include <vector>

namespace ip_filter {

using address_t = std::array<uint8_t, 4>;
using address_list = std::vector<address_t>;

namespace address {

inline auto from_string(const std::string &address) noexcept
    -> ip_filter::address_t {
  auto dot = address.find('.');
  uint8_t first_octet = std::stoul(address.substr(0, dot));
  auto second_dot = address.find('.', dot + 1);
  uint8_t second_octet = std::stoul(address.substr(dot + 1, second_dot));
  auto third_dot = address.find('.', second_dot + 1);
  uint8_t third_octet = std::stoul(address.substr(second_dot + 1, third_dot));
  uint8_t fourth_octet = std::stoul(address.substr(third_dot + 1));
  return {first_octet, second_octet, third_octet, fourth_octet};
}

inline auto to_string(const address_t &address) noexcept -> std::string {
  std::ostringstream buf{};
  buf << static_cast<int>(address[0]) << '.'  //
      << static_cast<int>(address[1]) << '.'  //
      << static_cast<int>(address[2]) << '.'  //
      << static_cast<int>(address[3]);
  return buf.str();
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
