project(Solana.Core.Network)

file(
    GLOB
    HEADER_LIST
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/include")
 file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADER_LIST}
        Websocket.cpp
        include/Solana/Core/Network/Websocket.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Solana.Core.Common
        OpenSSL::Crypto
        OpenSSL::SSL
        nlohmann_json::nlohmann_json)

find_package(Boost REQUIRED COMPONENTS
        url
        system
        thread
        headers
        coroutine)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Boost::url
        Boost::thread
        Boost::coroutine)

target_include_directories(${PROJECT_NAME} PUBLIC include)