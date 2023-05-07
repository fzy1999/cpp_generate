cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_C_STANDARD 20)
# to fix problem that can not find stddef.h
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I /home/sxx/.local/lib/clang/17/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fno-limit-debug-info")
# set(CMAKE_CXX_FLAGS "-stdlib=libstdc++ ${CMAKE_CXX_FLAGS}")
set(CMAKE_BUILD_TYPE "Debug")

project(cpp_generator)

enable_testing()


# add_subdirectory(library)
# add_subdirectory(generator)

