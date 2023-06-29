#include <algorithm>

#include <gtest/gtest.h>
#include <ip_filter.h>

using ip_filter::address_t;

TEST(FilterTest, ComparatorLess) {  // NOLINT

  ASSERT_TRUE(
      ip_filter::less(address_t{{1, 1, 1, 1}}, address_t{{1, 2, 1, 1}}));
  ASSERT_FALSE(
      ip_filter::less(address_t{{1, 2, 1, 1}}, address_t{{1, 1, 1, 1}}));
  ASSERT_FALSE(
      ip_filter::less(address_t{{2, 1, 1, 1}}, address_t{{1, 1, 1, 1}}));
}

TEST(FilterTest, ComparatorGreater) {  // NOLINT
  ASSERT_FALSE(
      ip_filter::greater(address_t{{1, 1, 1, 1}}, address_t{{1, 2, 1, 1}}));
  ASSERT_TRUE(
      ip_filter::greater(address_t{{1, 2, 1, 1}}, address_t{{1, 1, 1, 1}}));
  ASSERT_TRUE(
      ip_filter::greater(address_t{{2, 1, 1, 1}}, address_t{{1, 1, 1, 1}}));
}

TEST(FilterTest, SortDescending) {  // NOLINT
  auto ip_list = ip_filter::address_list{
      address_t{{1, 1, 1, 1}},  //
      address_t{{1, 2, 1, 1}},  //
      address_t{{1, 10, 1, 1}}  //
  };

  auto expected = ip_filter::address_list{
      address_t{{1, 10, 1, 1}},  //
      address_t{{1, 2, 1, 1}},   //
      address_t{{1, 1, 1, 1}},   //
  };

  ip_filter::sort(ip_list, ip_filter::greater);
  ASSERT_EQ(ip_list, expected);
}

TEST(FilterTest, FilterIf) {  // NOLINT
  auto ip_list = ip_filter::address_list{
      address_t{{1, 1, 1, 1}},     //
      address_t{{1, 2, 1, 1}},     //
      address_t{{1, 10, 1, 1}},    //
      address_t{{46, 70, 1, 1}},   //
      address_t{{46, 70, 1, 2}},   //
      address_t{{60, 70, 1, 46}},  //
      address_t{{60, 70, 46, 2}},  //
  };

  using ip_filter::filter_if;

  // Get addresses with first octet eq 1
  ASSERT_EQ(
      filter_if(ip_list,
                [](const auto &address) { return address.to_bytes()[0] == 1; }),
      (ip_filter::address_list{
          address_t{{1, 1, 1, 1}},   //
          address_t{{1, 2, 1, 1}},   //
          address_t{{1, 10, 1, 1}},  //
      }));

  // Get addresess with first two octets is 46 and 7
  ASSERT_EQ(filter_if(ip_list,
                      [](const auto &address) {
                        auto bytes = address.to_bytes();
                        return bytes[0] == 46 && bytes[1] == 70;
                      }),
            (ip_filter::address_list{
                address_t{{46, 70, 1, 1}},  //
                address_t{{46, 70, 1, 2}},  //
            }));

  // Get addresses with any 46 octet
  ASSERT_EQ(filter_if(ip_list,
                      [](const auto &address) {
                        auto bytes = address.to_bytes();
                        return std::any_of(
                            bytes.begin(), bytes.end(),
                            [](const auto &e) { return e == 46; });
                      }),
            (ip_filter::address_list{
                address_t{{46, 70, 1, 1}},   //
                address_t{{46, 70, 1, 2}},   //
                address_t{{60, 70, 1, 46}},  //
                address_t{{60, 70, 46, 2}},  //
            }));
}

TEST(FilterTest, AddressToString) {  // NOLINT
  using namespace ip_filter::address;
  ASSERT_EQ(to_string(ip_filter::address_t{{1, 2, 3, 4}}), "1.2.3.4");
}