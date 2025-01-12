cmake_minimum_required(VERSION 3.16)

project(zack_memory_manager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(src/MemoryPool DIR_MEMORY_POOL)

add_executable(zack_memory_manager ${DIR_MEMORY_POOL})
target_include_directories(zack_memory_manager PRIVATE include/)
