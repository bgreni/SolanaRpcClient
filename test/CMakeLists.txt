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

foreach(X IN ITEMS EncodingTests)
    add_executable(${X} ${X}.cpp)
    target_link_libraries(${X} Solana.Core.Common GTest::gtest_main)
    gtest_discover_tests(${X})
endforeach()