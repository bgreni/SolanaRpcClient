#include <gtest/gtest.h>
#include "Solana/Core/Encoding/Base58.hpp"
#include "Solana/Core/Account/Account.hpp"
#include <string_view>
#include "Solana/Core/Types/Types.hpp"
#include "Solana/Core/Transaction/TransactionBuilder.hpp"
#include "Solana/Core/Programs/System/System.hpp"
#include "Solana/Core/Crypto/Crypto.hpp"

#define CLASS Encoding_tests
using namespace Solana::Encoding;
using namespace Solana;
using namespace Solana::Crypto;
using namespace Solana::Transaction;

namespace {
    const std::string pubKeyString = "G3QzaxUKTxsrb2yY3gsW59tjvJCktrux54XedNY6BAJo";
}

LAYOUT(TestAccount, (u32, t1), (u16, t2))

TEST(CLASS, Pukey_B58) {
    const auto decoded = *Base58::Decode(pubKeyString);
    EXPECT_EQ(pubKeyString, Base58::Encode(decoded));
}

TEST(CLASS, TestSerializePubkey) {
    auto key = Pubkey{2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 34, 43, 43, 43, 34, 56, 56, 56, 45, 98};
    Buffer buf{};
    key.serialize(buf);
    auto expected = Buffer{2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 34, 43, 43, 43, 34, 56, 56, 56, 45, 98};
    ASSERT_EQ(expected, buf);
}

TEST(CLASS, TestSerializeCompactArrayPubkey) {
    auto arr = CompactArray<Pubkey>{
            Pubkey{2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 34, 43, 43, 43, 34, 56, 56, 56, 45, 98},
            Pubkey{2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 74, 43, 43, 43, 34, 56, 56, 56, 45, 98}
    };

    Buffer buf{};
    arr.serialize(buf);

    auto expected = Buffer{2,
                           2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 34, 43, 43, 43, 34, 56, 56, 56, 45, 98,
                           2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 74, 43, 43, 43, 34, 56, 56, 56, 45, 98
                           };
    EXPECT_EQ(expected, buf);
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

TEST(CLASS, CompactArraySerializationTest) {
    auto arr = CompactArray<u8> {
        1, 255, 67
    };
    Buffer buf; arr.serialize(buf);
    auto expected = Buffer{3, 1, 255, 67};
    ASSERT_EQ(expected, buf);
}

TEST(CLASS, HeaderSerializationTest) {
    auto header = Header{};
    header.requiredSigs = 3;
    header.readOnlyAddresses = 2;
    header.readOnlyAddressNoSig = 1;
    Buffer buf;
    header.serialize(buf);
    auto expected = Buffer{ 3, 2, 1 };
    EXPECT_EQ(expected, buf);
}

TEST(CLASS, InstructionSerializationTest) {
    LAYOUT(TestLayout, (u32, t1), (u64, t2))
    auto ins = CompiledInstruction {
        .programIndex = 3,
        .addressIndices = CompactArray<u32>{ 12, 34 },
        .data = TestLayout{.t1 = 23, .t2 = 100}.encode()
    };
    Buffer buf;
    ins.serialize(buf);
    auto expected = Buffer{
        3, 0, 0, 0,
        2, 12, 0, 0, 0,
        34, 0, 0, 0,
        12, 23, 0, 0, 0,
        100, 0, 0, 0, 0, 0, 0, 0,
    };
    EXPECT_EQ(expected, buf);
}

TEST(CLASS, TxnMessageSerializationTest) {
    auto kp = Keypair::fromSecretKey("3ffS3Y7v2iVFjpxe83WK6RxzYwCpfbVwvvEyuG52pyrvf6umUiVXUXLWKsHwRUKUtyhP99LfV4ciNYuWx2gRhhKd");

    auto builder = TransactionBuilder(
            BlockHash::fromString("4C76AqhSHrWND8tuqvZ37p62ssdtK4NGsfCm5kMUhNJt"), kp.pubkey)
            .add(Programs::System::Transfer(
//                            Pubkey::fromString("J9BU6Xo7G2BEct4tfEd2SVqMA2P7x8sTPyNq8ibm5hM2"),
                    Pubkey::fromString("J9BU6Xo7G2BEct4tfEd2SVqMA2P7x8sTPyNq8ibm5hM2"),
                    Pubkey::fromString("STEPNq2UGeGSzCyGVr2nMQAzf8xuejwqebd84wcksCK"),
                    100
            ).toInstruction());
    builder.sign(kp);

    auto message = builder.compileMessage();

    auto header = Header{};
    header.requiredSigs = 2;
    header.readOnlyAddresses = 0;
    header.readOnlyAddressNoSig = 1;
    const auto expected = Message {
        .header = header,
        .addresses = CompactArray<Pubkey>{
            Pubkey::fromString("6fY6rYZyJcNJsBkQkkAS64nS4LRWcLdkKAs1eYWqJpEb"),
            Pubkey::fromString("J9BU6Xo7G2BEct4tfEd2SVqMA2P7x8sTPyNq8ibm5hM2"),
            Pubkey::fromString("STEPNq2UGeGSzCyGVr2nMQAzf8xuejwqebd84wcksCK"),
            Pubkey::fromString("11111111111111111111111111111111")
        },
        .recentBlockhash = BlockHash::fromString("4C76AqhSHrWND8tuqvZ37p62ssdtK4NGsfCm5kMUhNJt"),
        .instructions = CompactArray<CompiledInstruction> {
            CompiledInstruction {
                .programIndex = 3,
                .addressIndices = {1, 2},
                .data = Buffer{2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0}
            }
        }
    };

    ASSERT_EQ(expected, message);

    const std::string expectedTxn = "5E1UgTjFsP3vvX8RxgXgXMBq6LPcgU9amFnj9gbgkmMkUy2RhGfpjRGB9BYEwdNDQyPV4VR4cmMpFyLukpyUWZEgSCm4DNaZn25PijmyM5zCmgSTF8gff5NhLrVkeymFkPZayJpexxPG1QurskRHeVjMiPoNYoXqgTgpqkkUdkpbtjP3F36nx3Urk8quw4LSREtUSS1s75i9yW12wwfAa7RPdkU4zvHBXNQVyR1mQgcQ7hBUWmEtVZi7";

    ASSERT_EQ(expectedTxn, builder.serializeMessage().toString());
}