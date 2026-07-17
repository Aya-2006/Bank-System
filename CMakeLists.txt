cmake_minimum_required(VERSION 3.10)
project(BankSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(bank_system ${SOURCES})

set(PG_CONFIG "/Applications/Postgres.app/Contents/Versions/18/bin/pg_config")

execute_process(COMMAND ${PG_CONFIG} --includedir OUTPUT_VARIABLE PG_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${PG_CONFIG} --libdir OUTPUT_VARIABLE PG_LIB_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "PostgreSQL include dir: ${PG_INCLUDE_DIR}")
message(STATUS "PostgreSQL lib dir: ${PG_LIB_DIR}")

target_include_directories(bank_system PRIVATE src ${PG_INCLUDE_DIR})
target_link_directories(bank_system PRIVATE ${PG_LIB_DIR})
target_link_libraries(bank_system PRIVATE pq)
