cmake_minimum_required(VERSION 3.26.4)
project(starting-conan-cmake-boost-project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.82.0 REQUIRED system filesystem)

add_executable(starting-conan-cmake-boost-project main.cpp)
target_link_libraries(starting-conan-cmake-boost-project PRIVATE Boost::headers Boost::system Boost::filesystem)
