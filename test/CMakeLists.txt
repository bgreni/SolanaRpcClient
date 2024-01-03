project(Tests)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

foreach(X IN ITEMS EncodingTests JsonReplyCompileTest CryptoTests)
    add_executable(${X} ${X}.cpp)
    target_link_libraries(${X} GTest::gtest_main Solana.Rpc Solana.Core.Programs)
    gtest_discover_tests(${X})
endforeach()