cmake_minimum_required(VERSION 3.0)  
project( kinect )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Debug" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

set( src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )

# OpenCV
find_package(OpenCV REQUIRED)
add_library (freenect_cv SHARED ${src_dir}/libfreenect_cv.cpp)
set_target_properties (freenect_cv PROPERTIES
  VERSION ${PROJECT_VER}
  SOVERSION ${PROJECT_APIVER})

include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR}/include/c_sync )

target_link_libraries (freenect_cv freenect_sync ${OpenCV_LIBS})

add_executable(freenect-cvdemo ${src_dir}/cvdemo.cpp)
target_link_libraries(freenect-cvdemo freenect freenect_sync freenect_cv ${OpenCV_LIBS})