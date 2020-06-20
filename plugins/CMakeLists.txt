add_subdirectory(StaticMap)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
 


find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

# Build our plugin
add_library(gazebo_usv_dynamics_plugin SHARED usv_dynamics_plugin/gazebo_usv_dynamics_plugin.cpp)
target_link_libraries(gazebo_usv_dynamics_plugin ${GAZEBO_libraries})
target_link_libraries (gazebo_usv_dynamics_plugin Eigen3::Eigen)
install(TARGETS gazebo_usv_dynamics_plugin DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_library(LiftDragPlugin SHARED liftdrag_plugin/liftdrag_plugin.cpp)
target_link_libraries (LiftDragPlugin Eigen3::Eigen)
install(TARGETS LiftDragPlugin DESTINATION ${PROJECT_SOURCE_DIR}/bin)

