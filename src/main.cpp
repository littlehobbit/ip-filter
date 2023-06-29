#include <iostream>

#include <ip_filter.h>
#include <utils.h>

constexpr uint8_t OCTET_46 = 46;
constexpr uint8_t OCTET_70 = 70;

int main(int /*argc*/, char * /*argv*/[]) {
  auto addresses = utils::read_addresses(std::cin);
  ip_filter::sort(addresses, ip_filter::greater);

  utils::transform_print(std::cout, addresses, ip_filter::address::to_string);

  {
    auto with_front_1 = ip_filter::filter_if(
        addresses, [](const auto &addr) { return addr.to_bytes()[0] == 1; });
    utils::transform_print(std::cout, with_front_1,
                           ip_filter::address::to_string);
  }

  {
    auto with_front_46_70 =
        ip_filter::filter_if(addresses, [](const auto &addr) {
          auto bytes = addr.to_bytes();
          return bytes[0] == OCTET_46 && bytes[1] == OCTET_70;
        });
    utils::transform_print(std::cout, with_front_46_70,
                           ip_filter::address::to_string);
  }

  {
    auto with_any_46 = ip_filter::filter_if(addresses, [](const auto &addr) {
      auto bytes = addr.to_bytes();
      return std::any_of(bytes.begin(), bytes.end(),
                         [](const auto &e) { return e == OCTET_46; });
    });
    utils::transform_print(std::cout, with_any_46,
                           ip_filter::address::to_string);
  }
}
