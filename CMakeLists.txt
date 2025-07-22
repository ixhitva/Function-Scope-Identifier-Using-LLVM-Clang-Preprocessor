cmake_minimum_required(VERSION 3.13)
project(FunctionScopeIdentifier)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    src/main.cpp
    src/FunctionVisitor.cpp
    src/FunctionScopeConsumer.cpp
    src/FunctionScopeAction.cpp
)

add_executable(FunctionScopeIdentifier ${SOURCE_FILES})

target_include_directories(FunctionScopeIdentifier PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
    include
)

target_link_libraries(FunctionScopeIdentifier
    clangTooling
    clangBasic
    clangASTMatchers
)
