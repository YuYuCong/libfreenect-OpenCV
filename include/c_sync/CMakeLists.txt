######################################################################################
# C Synchronous Interface
######################################################################################

set(THREADS_USE_PTHREADS_WIN32 true)
find_package(Threads REQUIRED)
include_directories(${THREADS_PTHREADS_INCLUDE_DIR})

add_library (freenect_sync SHARED libfreenect_sync.c)
add_library (freenect_sync_static STATIC libfreenect_sync.c)
set_target_properties (freenect_sync_static PROPERTIES OUTPUT_NAME freenect_sync)

set_target_properties (freenect_sync PROPERTIES
  VERSION ${PROJECT_VER}
  SOVERSION ${PROJECT_APIVER})

target_link_libraries (freenect_sync freenect ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (freenect_sync_static freenect ${CMAKE_THREAD_LIBS_INIT})
