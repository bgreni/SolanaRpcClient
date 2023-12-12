
set(PN solana_rpc)

file(
    GLOB
    HEADER_LIST
    CONFIGURE_DEPENDS
    "${solana_rpc_cpp_SOURCE_DIR}/include/solana_rpc")
file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(${PN} ${SOURCES} ${HEADER_LIST})
#target_include_directories(${PN} PUBLIC ../include)
#if(Boost_FOUND)
target_include_directories(${PN} PUBLIC ../include ${Boost_INCLUDE_DIRS})
#    target_link_libraries(${PN} PUBLIC Boost::system)
#endif(Boost_FOUND)

target_link_libraries(${PN} PUBLIC
        Boost::headers
        Boost::boost
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
