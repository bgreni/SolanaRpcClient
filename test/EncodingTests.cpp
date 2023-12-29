#include <gtest/gtest.h>
#include "Solana/Core/Encoding/Base58.hpp"
#include "Solana/Core/Account/Account.hpp"
#include <string_view>
#include "Solana/Core/Types/Types.hpp"

#define CLASS Encoding_tests
using namespace Solana::Encoding;
using namespace Solana;

namespace {
    const std::string pubKeyString = "G3QzaxUKTxsrb2yY3gsW59tjvJCktrux54XedNY6BAJo";
}

LAYOUT(TestAccount, (u32, t1), (u16, t2))

TEST(CLASS, Pukey_B58) {
    const auto decoded = *Base58::Decode(pubKeyString);
    EXPECT_EQ(pubKeyString, Base58::Encode(decoded));
}

TEST(CLASS, AccountSerialization) {
    auto account = TestAccount {
        .t1 = 120,
        .t2 = 45
    };
    auto serialized = account.encode();
    account.t1 = 200;
    account.decode(serialized);
    auto orig = TestAccount {
        .t1 = 120,
        .t2 = 45
    };
    EXPECT_TRUE(account == orig);
}