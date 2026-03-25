cmake_minimum_required(VERSION 3.16)
project(monkeycpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(monkeycpp
  src/main.cpp
  src/token.cpp
  src/lexer.cpp
  src/parser.cpp
  src/object.cpp
  src/environment.cpp
  src/builtins.cpp
  src/evaluator.cpp
)

target_include_directories(monkeycpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
