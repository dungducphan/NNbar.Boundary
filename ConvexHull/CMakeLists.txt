cmake_minimum_required(VERSION 3.12)
project(ConvexHull)

set(CMAKE_CXX_STANDARD 17)

if(APPLE)
    set(BOOST_INCLUDE_DIR /usr/local/Cellar/boost/1.63.0/include/)
    set(BOOST_LIBRARY_DIR /usr/local/Cellar/boost/1.63.0/lib)
    find_package(BOOST COMPONENTS SYSTEM FILESYSTEM REQUIRED)
endif()

if(UNIX)
    set(BOOST_INCLUDE_DIR /usr/include/boost/)
    set(BOOST_LIBRARY_DIR /usr/lib/x86_64-linux-gnu/)
endif()

include_directories(${BOOST_INCLUDE_DIR})
link_directories(${BOOST_LIBRARY_DIR})

add_library(ConvexHull SHARED ClusterConvexHullEstimator.cpp ClusterConvexHullEstimator.h ${BOOST_LIBRARIES})

add_executable(UnitTest UnitTest/UnitTest.cpp)
target_link_libraries(UnitTest ConvexHull)