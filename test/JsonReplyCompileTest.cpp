#include <gtest/gtest.h>
#include "Solana/Rpc/Rpc.hpp"

#define CLASS RepyCompileTest


// This is just to make sure these things serializeMessage

using namespace Solana;

TEST(CLASS, GetAccountInfo) {
    auto res = WithJsonReply<GetAccountInfo<>>("placeholder");
    EXPECT_TRUE(true);
}