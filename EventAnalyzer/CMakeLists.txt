cmake_minimum_required(VERSION 3.12)
project(EventAnalyzer)

set(CMAKE_CXX_STANDARD 17)
if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS -fext-numeric-literals)
endif()

if(APPLE)
    set(BOOST_INCLUDE_DIR /usr/local/Cellar/boost/1.63.0/include/)
    set(BOOST_LIBRARY_DIR /usr/local/Cellar/boost/1.63.0/lib)
    find_package(BOOST COMPONENTS SYSTEM FILESYSTEM REQUIRED)
endif()

if(UNIX AND NOT APPLE)
    set(BOOST_INCLUDE_DIR /usr/include/boost/)
    set(BOOST_LIBRARY_DIR /usr/lib/x86_64-linux-gnu/)
endif()

find_package(ROOT REQUIRED)

include(${ROOT_USE_FILE})

include_directories(
        ../ConvexHull/
        ../SmallestEnclosingCircle/
        ${BOOST_INCLUDE_DIR}
)

link_directories(
        ${BOOST_LIBRARY_DIR}
        ../ConvexHull/cmake-build-debug/
        ../SmallestEnclosingCircle/cmake-build-debug/
)

add_executable(EventAnalyzer main.cpp EventAnalyzer.cpp EventAnalyzer.h)
target_link_libraries(EventAnalyzer ${ROOT_LIBRARIES} Core Tree ConvexHull ClusterMinimalEnclosingCircle)