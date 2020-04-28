cmake_minimum_required(VERSION 3.10)

project(ctci)

file(GLOB_RECURSE ctci_SOURCES src/*.cpp )
file(GLOB_RECURSE ctci_HEADERS include/*.hpp)

include_directories(include)

foreach( testsourcefile ${ctci_SOURCES} )

    get_filename_component(testname ${testsourcefile} NAME)
    string( REPLACE ".cpp" "" testname ${testname} )

    add_executable( ${testname} ${testsourcefile} )

endforeach( testsourcefile ${ctci_SOURCES} )