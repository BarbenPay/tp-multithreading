cmake_minimum_required(VERSION 3.14)
project(DistributedSystem CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(boss Boss.cpp)
target_link_libraries(boss PRIVATE cpr::cpr nlohmann_json::nlohmann_json)

add_executable(minion Minion.cpp)
target_link_libraries(minion PRIVATE cpr::cpr nlohmann_json::nlohmann_json)