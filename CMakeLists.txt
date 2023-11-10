cmake_minimum_required(VERSION 3.14)
project(EndianLib VERSION 0.2.1 DESCRIPTION "EndianLib: A C++ library for endian handling")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the library target
add_library(EndianLib INTERFACE)
target_include_directories(EndianLib INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# For installing (optional, but useful for library users)
include(GNUInstallDirs)
install(TARGETS EndianLib
    EXPORT endianlib-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/EndianLib
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Testing
enable_testing()

# FetchContent for GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(endian_test tests/endian_test.cpp)
target_link_libraries(endian_test PRIVATE EndianLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(endian_test)
