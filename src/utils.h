#ifndef __UTILS_H_SUGR41SK6JIZ__
#define __UTILS_H_SUGR41SK6JIZ__

#include <algorithm>
#include <iostream>
#include <istream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>

#include "ip_filter.h"

namespace utils {

inline auto read_addresses(std::istream &in) -> ip_filter::address_list {
  ip_filter::address_list res{};

  std::string line;
  while (std::getline(in, line)) {
    std::istringstream line_stream{line};

    std::string address{};
    std::string dummy{};
    line_stream >> address >> dummy >> dummy;

    res.push_back(ip_filter::address::from_string(address));
  }

  return res;
}

template <typename Container, typename Transform>
inline auto transform_print(std::ostream &out, const Container &container,
                            Transform &&transformer) noexcept {
  std::transform(
      std::begin(container), std::end(container),
      std::ostream_iterator<decltype(transformer(container[0]))>{out, "\n"},
      transformer);
}

}  // namespace utils

#endif  // __UTILS_H_SUGR41SK6JIZ__
