cmake_minimum_required(VERSION 3.15)
project(MyProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch Catch2
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.1
)
FetchContent_MakeAvailable(catch2)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Collect project sources
file(GLOB_RECURSE SRC_SOURCES "src/*.cpp")

# Create test executable
add_executable(tests
    tests/unit_tests/test_encrypt_decrypt.cpp
    ${SRC_SOURCES}   # Include project sources
)

# Include src headers
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Link Catch2 and OpenSSL
target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
    OpenSSL::Crypto
)
