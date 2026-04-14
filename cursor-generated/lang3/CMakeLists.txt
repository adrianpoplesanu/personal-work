cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

add_executable(main
  src/main.cpp
  src/token.cpp
  src/lexer.cpp
  src/parser.cpp
  src/object.cpp
  src/environment.cpp
  src/builtins.cpp
  src/evaluator.cpp
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(main PRIVATE Threads::Threads)
