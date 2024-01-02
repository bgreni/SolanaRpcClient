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
    const auto decoded = Pubkey::fromString(pubKeyString);
    EXPECT_EQ(pubKeyString, decoded.toStdString());
}

TEST(CLASS, TestSerializePubkey) {
    auto key = Pubkey{2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 34, 43, 43, 43, 34, 56, 56, 56, 45, 98};
    Buffer buf{};
    key.serialize(buf);
    auto expected = Buffer{2, 32, 45, 56, 34, 64, 64, 34, 34, 35, 34, 65, 57, 34, 45, 34, 45, 64, 34, 43, 34, 34, 34, 43, 43, 43, 34, 56, 56, 56, 45, 98};
    EXPECT_EQ(expected, buf);
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
    EXPECT_EQ(expected, buf);
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
        .addressIndices = CompactArray<u8>{ 12, 34 },
        .data = TestLayout{.t1 = 23, .t2 = 100}.encode()
    };
    Buffer buf;
    ins.serialize(buf);
    auto expected = Buffer{
        3,
        2, 12, 34,
        12, 23, 0, 0, 0,
        100, 0, 0, 0, 0, 0, 0, 0,
    };
    EXPECT_EQ(expected, buf);
}

TEST(CLASS, CompactArrayCompiledInstructionSerializationTest) {
    auto arr = CompactArray<CompiledInstruction> {
        CompiledInstruction {
            .programIndex = 3,
            .addressIndices = {1, 2},
            .data = Buffer{2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0}
        }
    };

    Buffer buf{};
    arr.serialize(buf);

    auto expected = Buffer{
        1, 3,
        2, 1, 2,
        12, 2, 0, 0, 0,
        100, 0, 0, 0, 0, 0, 0, 0,
    };

    EXPECT_EQ(expected, buf);
}

TEST(CLASS, TransferSerializationTest) {
    auto kp = Keypair::fromSecretKey("3ffS3Y7v2iVFjpxe83WK6RxzYwCpfbVwvvEyuG52pyrvf6umUiVXUXLWKsHwRUKUtyhP99LfV4ciNYuWx2gRhhKd");
    auto transfer = Programs::System::Transfer(
        kp.pubkey,
        Pubkey::fromString("5dEU1ec2Dw6C8v1jhtnRN6ZYnnVE54Yn3hJDh4U4fyZJ"),
        100
    );

    auto buf = transfer.data.encode();
    auto expected = Buffer{2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(buf, expected);
}

TEST(CLASS, TxnMessageSerializationTest) {

    auto signer = Pubkey::fromString("6fY6rYZyJcNJsBkQkkAS64nS4LRWcLdkKAs1eYWqJpEb");

    auto builder = TransactionBuilder(
            BlockHash::fromString("4C76AqhSHrWND8tuqvZ37p62ssdtK4NGsfCm5kMUhNJt"), signer)
            .add(Programs::System::Transfer(
                    signer,
                    Pubkey::fromString("5dEU1ec2Dw6C8v1jhtnRN6ZYnnVE54Yn3hJDh4U4fyZJ"),
                    100
            ).toInstruction());

    auto message = builder.compileMessage();

    auto header = Header{};
    header.requiredSigs = 1;
    header.readOnlyAddresses = 0;
    header.readOnlyAddressNoSig = 1;
    const auto expected = Message(
        header,
        AddressSection{
            Pubkey::fromString("6fY6rYZyJcNJsBkQkkAS64nS4LRWcLdkKAs1eYWqJpEb"),
            Pubkey::fromString("5dEU1ec2Dw6C8v1jhtnRN6ZYnnVE54Yn3hJDh4U4fyZJ"),
            Pubkey::fromString("11111111111111111111111111111111")
        },
        BlockHash::fromString("4C76AqhSHrWND8tuqvZ37p62ssdtK4NGsfCm5kMUhNJt"),
        CompactArray<CompiledInstruction> {
            CompiledInstruction {
                .programIndex = 2,
                .addressIndices = {0, 1},
                .data = Buffer{2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0}
            }
        }
    );

    EXPECT_EQ(expected, message);

    const std::string expectedTxn = "87PYsNDxaKYiA1gma7e34RnUZ5aXvZuKdzHjYCuPWhjHGHMoH6q2DDqrZX6XzEWHhteu7VFK4bNy1v1AKUFZjmNNvHPTVH8vZ5x3JfbZ9mwScaVjYbghDUaYt48wT75v9WLMvpzQdHD1BXh8pYydufKgasmYGCAayxE1Vf4X9zeokymCvum1q4r2wgqCZZuLRFKrUCVJJCm5";

    const auto decoded = *Encoding::Base58::Decode(expectedTxn);

    const auto actual = builder.serializeMessage();

    EXPECT_EQ(Buffer(decoded), actual);

    EXPECT_EQ(
        decoded.size(),
        actual.size());

    EXPECT_EQ(expectedTxn, actual.toString());
}