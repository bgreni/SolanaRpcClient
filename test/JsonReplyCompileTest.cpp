#include <gtest/gtest.h>
#include "Solana/Rpc/Rpc.hpp"

#define CLASS RepyCompileTest


// This is just to make sure these things compile

using namespace Solana;

TEST(CLASS, CompileTest) {
    WithJsonReply<GetAccountInfo<>>("placeholder");
    WithJsonReply<GetBalance>("placeholder");
    WithJsonReply<GetBlock>(0);
    WithJsonReply<GetBlockHeight>();
    WithJsonReply<GetBlockProduction>();
    WithJsonReply<GetLatestBlockhash>();
    WithJsonReply<SendTransaction>("placeholder");
    WithJsonReply<SimulateTransaction>("placeholder");
}


