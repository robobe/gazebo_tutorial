

# Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

# Build our plugin
add_library(StaticMap SHARED StaticMapPlugin.cc)
target_link_libraries(StaticMap ${GAZEBO_libraries})
install(TARGETS StaticMap DESTINATION ${PROJECT_SOURCE_DIR}/bin)
