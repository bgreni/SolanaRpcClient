project(Solana.Core.Common)

file(
        GLOB
        HEADER_LIST
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADER_LIST})

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Boost::system
        PRIVATE
        OpenSSL::Crypto)

target_include_directories(${PROJECT_NAME} PUBLIC include)