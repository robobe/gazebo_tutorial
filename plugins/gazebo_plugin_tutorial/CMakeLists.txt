find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(hello_world SHARED hello_world.cc)
target_link_libraries(hello_world ${GAZEBO_LIBRARIES})

add_library(model_push SHARED model_push.cc)
target_link_libraries(model_push ${GAZEBO_LIBRARIES})
message(${PROJECT_SOURCE_DIR})
install(TARGETS hello_world DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_library(sub_demo SHARED subscriber_demo.cpp)
target_link_libraries(sub_demo 
    ${GAZEBO_LIBRARIES})
install(TARGETS sub_demo DESTINATION ${PROJECT_SOURCE_DIR}/bin)

# https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html