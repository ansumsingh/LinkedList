cmake_minimum_required(VERSION 2.7)
project(LinkedListTest)

#for c++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
#find_package(apriltags REQUIRED)
#find_package(Eigen3 REQUIRED)
#if_found(${EIGEN3_INCLUDE_DIRS})
	#message(${EIGEN3_LIBRARIES})

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})


add_executable(linkedListTest linkedListTest.cpp linkedList.hpp)



target_link_libraries(linkedListTest ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})

