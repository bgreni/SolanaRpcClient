cmake_minimum_required(VERSION 3.23)
project(SolanaCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

find_package(OpenSSL REQUIRED)

set(LIBRARY_NAME solana_rpc)

if (UNIX)
    add_compile_options("-fexceptions")
endif(UNIX)

add_subdirectory(Rpc)
add_subdirectory(Core)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(app main.cpp)
    target_link_libraries(app PRIVATE Solana.Rpc)
endif()