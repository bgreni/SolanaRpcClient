#include "Solana/Rpc/Rpc.hpp"

#include <iostream>

#include <string>
using namespace Solana;

int main() {


    auto rpc = Rpc(std::getenv("ENDPOINT"));
//    auto res = rpc.send(
//        GetBalance("FpscJFipKBoAFXjhXfrruWyhsoNFisu8H8kLDdw1k8yH",
//        GetBalance::Config{.commitment = "confirmed"}))
//        .get().result.value;

//    auto res = rpc.send(GetBlockHeight(
//            GetBlockHeight::Config{.commitment=CommitmentLevel::Finalized}
//            )).get().result.height;


    std::cout << res;

    return 0;
}