#include <algorithm>
#include <gtest/gtest.h>

#include <ip_filter.h>

TEST(FilterTest, ComparatorLess) {
  ASSERT_TRUE(ip_filter::less({1, 1, 1, 1}, {1, 2, 1, 1}));
  ASSERT_FALSE(ip_filter::less({1, 2, 1, 1}, {1, 1, 1, 1}));
  ASSERT_FALSE(ip_filter::less({2, 1, 1, 1}, {1, 1, 1, 1}));
}

TEST(FilterTest, ComparatorGreater) {
  ASSERT_FALSE(ip_filter::greater({1, 1, 1, 1}, {1, 2, 1, 1}));
  ASSERT_TRUE(ip_filter::greater({1, 2, 1, 1}, {1, 1, 1, 1}));
  ASSERT_TRUE(ip_filter::greater({2, 1, 1, 1}, {1, 1, 1, 1}));
}

TEST(FilterTest, SortDescending) {
  auto ip_list = ip_filter::address_list{
      {1, 1, 1, 1}, //
      {1, 2, 1, 1}, //
      {1, 10, 1, 1} //
  };

  auto expected = ip_filter::address_list{
      {1, 10, 1, 1}, //
      {1, 2, 1, 1},  //
      {1, 1, 1, 1},  //
  };

  ip_filter::sort(ip_list, ip_filter::greater);
  ASSERT_EQ(ip_list, expected);
}

TEST(FilterTest, FilterIf) {
  auto ip_list = ip_filter::address_list{
      {1, 1, 1, 1},    //
      {1, 2, 1, 1},    //
      {1, 10, 1, 1},   //
      {46, 70, 1, 1},  //
      {46, 70, 1, 2},  //
      {60, 70, 1, 46}, //
      {60, 70, 46, 2}, //
  };

  using ip_filter::filter_if;

  // Get addresses with first octet eq 1
  ASSERT_EQ(
      filter_if(ip_list, [](const auto &address) { return address[0] == 1; }),
      (ip_filter::address_list{
          {1, 1, 1, 1},  //
          {1, 2, 1, 1},  //
          {1, 10, 1, 1}, //
      }));

  // Get addresess with first two octets is 46 and 7
  ASSERT_EQ(filter_if(ip_list,
                      [](const auto &address) {
                        return address[0] == 46 && address[1] == 70;
                      }),
            (ip_filter::address_list{
                {46, 70, 1, 1}, //
                {46, 70, 1, 2}, //
            }));

  // Get addresses with any 46 octet
  ASSERT_EQ(filter_if(ip_list,
                      [](const auto &address) {
                        return std::any_of(
                            address.begin(), address.end(),
                            [](const auto &e) { return e == 46; });
                      }),
            (ip_filter::address_list{
                {46, 70, 1, 1},  //
                {46, 70, 1, 2},  //
                {60, 70, 1, 46}, //
                {60, 70, 46, 2}, //
            }));
}

TEST(FilterTest, AddressToString) {
  using namespace ip_filter::address;
  ASSERT_EQ(to_string({1, 2, 3, 4}), "1.2.3.4");
}