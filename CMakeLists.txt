set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(BUILD_1 main)
set(SOURCE_FILES_1 ./semantic-analyzer/semantics.c)
add_executable(${BUILD_1} ${SOURCE_FILES_1})