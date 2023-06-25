#include <iostream>

#include <ip_filter.h>
#include <utils.h>

int main(int argc, char *argv[]) {
  auto addresses = utils::read_addresses(std::cin);
  ip_filter::sort(addresses, ip_filter::greater);

  utils::transform_print(std::cout, addresses, ip_filter::address::to_string);

  {
    auto with_front_1 = ip_filter::filter_if(
        addresses, [](const auto &addr) { return addr[0] == 1; });
    utils::transform_print(std::cout, with_front_1,
                           ip_filter::address::to_string);
  }

  {
    auto with_front_46_70 =
        ip_filter::filter_if(addresses, [](const auto &addr) {
          return addr[0] == 46 && addr[1] == 70;
        });
    utils::transform_print(std::cout, with_front_46_70,
                           ip_filter::address::to_string);
  }

  {
    auto with_any_46 = ip_filter::filter_if(addresses, [](const auto &addr) {
      return addr[0] == 46 || addr[1] == 46 || addr[2] == 46 || addr[3] == 46;
    });
    utils::transform_print(std::cout, with_any_46,
                           ip_filter::address::to_string);
  }
}