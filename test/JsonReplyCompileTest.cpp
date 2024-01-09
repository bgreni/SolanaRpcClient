#include <gtest/gtest.h>
#include "Solana/Rpc/Rpc.hpp"

#define CLASS RpcTest


// This is just to make sure these things compile

using namespace Solana;

TEST(CLASS, CompileTest) {
    WithJsonReply<GetAccountInfo<>>("placeholder");
    WithJsonReply<GetBalance>("placeholder");
    WithJsonReply<GetBlock>(0);
    WithJsonReply<GetBlocks>(0, 5);
    WithJsonReply<GetBlockTime>(100);
    WithJsonReply<GetBlocksWithLimit>(100, 5);
    WithJsonReply<GetBlockHeight>();
    WithJsonReply<GetBlockProduction>();
    WithJsonReply<GetBlockCommitment>(0);
    WithJsonReply<GetLatestBlockhash>();
    WithJsonReply<GetSlot>();
    WithJsonReply<SendTransaction>("placeholder");
    WithJsonReply<SimulateTransaction>("placeholder");
}

TEST(CLASS, UrlParseTest) {
    auto res = Network::Url("https://api.mainnet-beta.solana.com/");
    EXPECT_EQ(res.service, "https");
    EXPECT_EQ(res.endpoint, "api.mainnet-beta.solana.com");
    EXPECT_EQ(res.targetBase, "/");
}

TEST(CLASS, UrlParseTestNoEndingSlash) {
    auto res = Network::Url("https://api.mainnet-beta.solana.com");
    EXPECT_EQ(res.service, "https");
    EXPECT_EQ(res.endpoint, "api.mainnet-beta.solana.com");
    EXPECT_EQ(res.targetBase, "");
}


TEST(CLASS, HeliusUrlParseTest) {
    auto res = Network::Url("https://mainnet.helius-rpc.com/?api-key=smd");
    EXPECT_EQ(res.service, "https");
    EXPECT_EQ(res.endpoint, "mainnet.helius-rpc.com");
    EXPECT_EQ(res.targetBase, "/?api-key=smd");
}


