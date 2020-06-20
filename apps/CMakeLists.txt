# cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_executable(cc camera_control.cpp)
target_link_libraries(cc ${GAZEBO_LIBRARIES})
install(TARGETS cc DESTINATION ${PROJECT_SOURCE_DIR}/bin)