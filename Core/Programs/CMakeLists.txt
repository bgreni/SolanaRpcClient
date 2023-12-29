project(Solana.Core.Programs)


file(
        GLOB
        HEADER_LIST
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/include")
file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADER_LIST})
target_link_libraries(${PROJECT_NAME} PUBLIC
        Solana.Core.Common)

target_include_directories(${PROJECT_NAME} PUBLIC include)