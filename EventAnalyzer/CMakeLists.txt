cmake_minimum_required(VERSION 3.12)
project(EventAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(BOOST_INCLUDE_DIR /usr/local/Cellar/boost/1.63.0/include/)
set(BOOST_LIBRARY_DIR /usr/local/Cellar/boost/1.63.0/lib)

find_package(ROOT REQUIRED)
find_package(BOOST COMPONENTS SYSTEM FILESYSTEM REQUIRED)

include(${ROOT_USE_FILE})

include_directories(
        /Users/dphan90/NOvA.NNbar/ConvexHull/
        /Users/dphan90/NOvA.NNbar/SmallestEnclosingCircle/
)

include_directories(${BOOST_INCLUDE_DIR})
link_directories(
        ${BOOST_LIBRARY_DIR}
        /Users/dphan90/NOvA.NNbar/ConvexHull/cmake-build-debug/
        /Users/dphan90/NOvA.NNbar/SmallestEnclosingCircle/cmake-build-debug/
)

add_executable(EventAnalyzer main.cpp EventAnalyzer.cpp EventAnalyzer.h)
target_link_libraries(EventAnalyzer ${ROOT_LIBRARIES} Core Tree ConvexHull ClusterMinimalEnclosingCircle)