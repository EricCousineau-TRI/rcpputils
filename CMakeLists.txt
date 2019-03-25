cmake_minimum_required(VERSION 3.5)

project(rcpputils)

find_package(ament_cmake REQUIRED)

# Default to C11
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(NOT WIN32)
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

ament_export_include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/find_library.cpp)
target_include_directories(${PROJECT_NAME}
  PUBLIC
  include
)
target_link_libraries(${PROJECT_NAME} dl)
ament_export_libraries(${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_lint_auto REQUIRED)

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wthread-safety -Werror)
  endif()

  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_basic test/test_basic.cpp)

  add_library(toy_test_library SHARED test/toy_test_library.cpp)
  ament_add_gtest(test_find_library test/test_find_library.cpp)
  target_link_libraries(test_find_library ${PROJECT_NAME} toy_test_library)
  set_tests_properties(test_find_library PROPERTIES
      ENVIRONMENT
        "_TOY_TEST_LIBRARY_DIR=$<TARGET_FILE_DIR:toy_test_library>;_TOY_TEST_LIBRARY=$<TARGET_FILE:toy_test_library>;_LIBRARY=$<TARGET_FILE:${PROJECT_NAME}>")
endif()

ament_package()

install(
  DIRECTORY include/
  DESTINATION include)
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)
