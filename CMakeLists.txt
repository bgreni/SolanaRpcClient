cmake_minimum_required(VERSION 3.23)
project(solana_rpc_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")


#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_STATIC_RUNTIME ON)

#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} address")
#set(CMAKE_OSX_ARCHITECTURES "x86_64")
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

#find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)
#find_package(Boost REQUIRED)
find_package(Boost COMPONENTS headers REQUIRED)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_STATIC_RUNTIME ON)

#if(Boost_FOUND)
##    include_directories(${Boost_INCLUDE_DIRS})
#    message(STATUS "Found boost")
#else()
#    message(FATAL_ERROR "Can't find boost")
#endif(Boost_FOUND)

set(LIBRARY_NAME solana_rpc)

add_subdirectory(src)