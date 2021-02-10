cmake_minimum_required(VERSION 3.10)

project(ctci)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE ctci_SOURCES src/Chapter_17_Hard/VolumeOfHistogram.cpp )
file(GLOB_RECURSE ctci_HEADERS include/*.hpp)

include_directories(include)

foreach( testsourcefile ${ctci_SOURCES} )

    get_filename_component(testname ${testsourcefile} NAME)
    string( REPLACE ".cpp" "" testname ${testname} )

    add_executable( ${testname} ${testsourcefile} )
    target_compile_features(${testname} PRIVATE cxx_std_17)
    target_link_libraries(${testname} Threads::Threads mysqlcppconn)

endforeach( testsourcefile ${ctci_SOURCES} )