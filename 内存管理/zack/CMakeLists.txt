cmake_minimum_required(VERSION 3.16)

project(zack_memory_manager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(src/MemoryPool DIR_MEMORY_POOL)
aux_source_directory(src/SimpleSharedPtr DIR_SIMPLE_SHARED_PTR)
aux_source_directory(src/SimpleUniquePtr DIR_SIMPLE_UNIQUE_PTR)

add_executable(zack_memory_manager ${DIR_MEMORY_POOL})
add_executable(zack_simpleshared_ptr ${DIR_SIMPLE_SHARED_PTR})
add_executable(zack_simpleunique_ptr ${DIR_SIMPLE_UNIQUE_PTR})

target_include_directories(zack_memory_manager PRIVATE include/)
target_include_directories(zack_simpleshared_ptr PRIVATE include/) 
target_include_directories(zack_simpleunique_ptr PRIVATE include/)

add_executable(zack_unique_ptr src/SmartPtr/uniquePtr.cpp)
target_include_directories(zack_unique_ptr PRIVATE include/)

add_executable(zack_shared_ptr src/SmartPtr/sharedPtr.cpp)
target_include_directories(zack_shared_ptr PRIVATE include/)

add_executable(zack_weak_ptr src/SmartPtr/weakPtr.cpp)
add_executable(zack_shared_weak_ptr src/SmartPtr/shared_weak_ptr.cpp)
add_executable(zack_filedeleter src/SmartPtr/fileDeleter.cpp)
add_executable(zack_lambda_deleter src/SmartPtr/lambdaDeleter.cpp)
