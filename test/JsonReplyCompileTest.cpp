#include <gtest/gtest.h>
#include "Solana/Rpc/Rpc.hpp"

#define CLASS RepyCompileTest


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


