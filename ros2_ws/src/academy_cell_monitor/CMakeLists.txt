cmake_minimum_required(VERSION 3.8)
project(academy_cell_monitor)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(cell_monitor src/cell_monitor.cpp)
target_compile_features(cell_monitor PUBLIC cxx_std_17)
target_include_directories(cell_monitor PRIVATE include)
ament_target_dependencies(cell_monitor rclcpp sensor_msgs std_msgs)

install(TARGETS cell_monitor DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY config launch DESTINATION share/${PROJECT_NAME})

include(CTest)
if(BUILD_TESTING)
  add_executable(test_freshness test/test_freshness.cpp)
  target_compile_features(test_freshness PUBLIC cxx_std_17)
  target_include_directories(test_freshness PRIVATE include)
  add_test(NAME freshness COMMAND test_freshness)
endif()

ament_package()
