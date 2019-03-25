// Copyright 2019 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "gtest/gtest.h"

#include "rcpputils/find_library.hpp"

namespace rcpputils {
namespace {

const char * get_lib_env_var() {
#ifdef _WIN32
  return "PATH";
#elif __APPLE__
  return "DYLD_LIBRARY_PATH";
#else
  return "LD_LIBRARY_PATH";
#endif
}

TEST(test_find_library, find_library) {
  // Get ground-truth values from CTest properties.
  const char * toy_lib_expected = getenv("_TOY_TEST_LIBRARY");
  EXPECT_NE(toy_lib_expected, nullptr);
  const char * toy_lib_dir = getenv("_TOY_TEST_LIBRARY_DIR");
  EXPECT_NE(toy_lib_dir, nullptr);

  // Set our relevant path variable.
  const int override = 1;
  setenv(get_lib_env_var(), toy_lib_dir, override);

  // Positive test.
  const std::string toy_lib_actual = find_library_path("toy_test_library");
  EXPECT_EQ(toy_lib_actual, toy_lib_expected);

  // (Hopefully) Negative test.
  const std::string bad_path = find_library_path(
      "this_is_a_junk_libray_name_please_dont_define_this_if_you_do_then_"
      "you_are_really_naughty");
  EXPECT_EQ(bad_path, "");
}

TEST(test_find_library, find_library_loaded) {
  const char * lib_expected = getenv("_LIBRARY");
  EXPECT_NE(lib_expected, nullptr);

  // Strip out environment.
  const int override = 1;
  setenv(get_lib_env_var(), "", override);

  // Use loaded.
  const std::string lib_actual = find_library_path("rcpputils");
  EXPECT_EQ(lib_actual, lib_expected);
}

}  // namespace
}  // namespace rcpputils
