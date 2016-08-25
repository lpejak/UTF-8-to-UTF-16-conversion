project(example)
cmake_minimum_required(VERSION 3.0)

add_executable(example example.cpp)
install(TARGETS example RUNTIME DESTINATION bin)
