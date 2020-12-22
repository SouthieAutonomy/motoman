cmake_minimum_required(VERSION 2.8.3)
project(motoman_driver)

add_compile_options(-std=c++11)

add_executable(test_alarm_reply test_alarm_reply.cpp)
target_link_libraries(test_alarm_reply ${catkin_LIBRARIES})
add_dependencies(test_alarm_reply ${catkin_EXPORTED_TARGETS})
