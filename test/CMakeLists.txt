find_package(RTTR CONFIG REQUIRED Core)

add_executable(test main.cpp)

# target_include_directories(test )

target_link_libraries(test RTTR::Core)