cmake_minimum_required(VERSION 3.15)
project(pgit CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#httplib
include(FetchContent)

FetchContent_Declare(httplib SYSTEM
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG a609330e4c6374f741d3b369269f7848255e1954 # v0.14.1
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(httplib)


add_library(includes INTERFACE)
target_include_directories(includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(pgit src/main.cpp)
target_compile_definitions(pgit PUBLIC CPPHTTPLIB_OPENSSL_SUPPORT)

target_link_libraries(pgit PUBLIC httplib includes)