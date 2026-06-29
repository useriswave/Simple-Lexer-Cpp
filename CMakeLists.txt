cmake_minimum_required(VERSION 3.22.0)
project(dumblang)
add_executable(${PROJECT_NAME} src/lexer/main.cpp src//lexer/lexer.cpp src/lexer/token.cpp src/lexer/filereader.cpp)

find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
