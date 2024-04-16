#include <gtest/gtest.h>

#include "Models/ServerSocket.hpp"

TEST(IP_tests, loopback_conversion) {
  ASSERT_EQ(string_to_ip("127.0.0.1"),uint32_t{0x7f000001});
}
TEST(IP_tests, local_area_ip) {
  ASSERT_EQ(string_to_ip("192.168.0.1"),uint32_t{0xC0A80001});
}
