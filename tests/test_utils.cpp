#include <sstream>

#include <gtest/gtest.h>

#include "ip_filter.h"
#include "utils.h"

using ip_filter::address_t;

TEST(UtilsTest, ReadAddressList_NonEmpty) { // NOLINT
  std::istringstream input{
      "113.162.145.156\t111\t0\n157.39.22.224\t5\t6\n79.180.73.190\t2\t1"};

  auto result = utils::read_addresses(input);
  ASSERT_EQ(result, (ip_filter::address_list{
                        address_t{{113, 162, 145, 156}},  //
                        address_t{{157, 39, 22, 224}},    //
                        address_t{{79, 180, 73, 190}}     //
                    }));
}

TEST(UtilsTest, ReadAddressList_Empty) {  // NOLINT
  std::istringstream input{""};
  auto result = utils::read_addresses(input);
  ASSERT_TRUE(result.empty());
}

TEST(UtilsTest, PrintsWithTransform) {  // NOLINT
  std::ostringstream output{};
  auto vector = std::vector{1, 2, 3, 4, 6, 6, 6, 6};
  utils::transform_print(output, vector, [](auto &e) { return 2 * e; });
  ASSERT_EQ(output.str(), "2\n4\n6\n8\n12\n12\n12\n12\n");
}

TEST(UtilsTest, PrintsAddresses) {  // NOLINT
  std::ostringstream output{};
  auto addresses =
      ip_filter::address_list{address_t{{1, 2, 3, 4}}, address_t{{6, 6, 6, 6}}};
  utils::transform_print(output, addresses, ip_filter::address::to_string);
  ASSERT_EQ(output.str(), "1.2.3.4\n6.6.6.6\n");
}