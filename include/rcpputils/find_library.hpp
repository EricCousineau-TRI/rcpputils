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

#ifndef RCPPUTILS__FIND_LIBRARY_H_
#define RCPPUTILS__FIND_LIBRARY_H_

#include <string>

namespace rcpputils {

/// Finds a library (using the appropriate shared-library environment variable,
/// e.g. `LD_LIBRARY_PATH` on Linux), and returns the absolute filesystem path
/// (including the appropriate prefix and suffix).
/**
 * \param[in] library_name Name of the library to find.
 */
std::string find_library_path(const std::string & library_name);

}  // namespace rcpputils

#endif  // RCPPUTILS__FIND_LIBRARY_H_
