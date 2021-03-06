cmake_minimum_required(VERSION 3.14)
project(my_project)

add_compile_options(-Wall -Wextra -pedantic -Werror)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  add_compile_options(-Wno-unused-lambda-capture)
endif()

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL ${CMAKE_CURRENT_SOURCE_DIR}/googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

FILE(GLOB TEST_SRCS tests/*.cpp)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/bsp-linux
)

add_executable(
  all_tests
  ${TEST_SRCS}
)
target_link_libraries(
  all_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(all_tests)

FILE(GLOB PROTOTYPEREADER_SRCS PrototypeReader/*.cpp)
add_executable(
  PrototypeReader
  ${PROTOTYPEREADER_SRCS}
)

FILE(GLOB PROTOTYPEBLINK_SRCS PrototypeBlink/*.cpp)
add_executable(
  PrototypeBlink
  ${PROTOTYPEBLINK_SRCS}
)

FILE(GLOB PROTOTYPEREADER_SRCS PrototypePinball/*.cpp)
add_executable(
  PrototypePinball
  ${PROTOTYPEREADER_SRCS}
)