cmake_minimum_required(VERSION 3.10)

project(cpp_generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I /home/sxx/.local/lib/clang/17/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fno-limit-debug-info")
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

# todo
set(TCLAP_INCLUDE_DIRS "$ENV{HOME}/miniconda3/include/tclap/Arg.h")  
include_directories(${TCLAP_INCLUDE_DIRS})

### LLVM and clang
find_package(LLVM REQUIRED)

message("found LLVM include directory at: \"" ${LLVM_INCLUDE_DIR} "\"")
message("found LLVM library directory at: \"" ${LLVM_LIBRARY_DIR} "\"")

include_directories(${LLVM_INCLUDE_DIR})
link_directories(${LLVM_LIBRARY_DIR})
###

find_package(inja CONFIG REQUIRED)

set(SOURCES
    main.cpp
    tools/files.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

# target_link_libraries(${PROJECT_NAME} PRIVATE reflection)
target_link_libraries(${PROJECT_NAME} PRIVATE pantor::inja)
target_link_libraries(${PROJECT_NAME} PRIVATE LLVM clang-cpp)


# configure_file(config.yaml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.yaml COPYONLY)
