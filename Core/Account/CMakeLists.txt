project(Solana.Core.Account)

file(
        GLOB
        HEADER_LIST
        CONFIGURE_DEPENDS
        "${solana_rpc_cpp_SOURCE_DIR}/include")
file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADER_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC include)

source_group(
        TREE "include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})