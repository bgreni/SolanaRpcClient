#include "Solana/Rpc/Rpc.hpp"

#include <iostream>

#include <string>
using namespace Solana;

int main() {
    auto rpc = Rpc(std::getenv("ENDPOINT"));

    auto res = rpc.send(GetBlockHeight());
    std::cout << res.get().result.height << "\n";

    auto jsonRes = rpc.send(WithJsonReply<GetBlockHeight>());
    std::cout << jsonRes.get().result << "\n";

    return 0;
}