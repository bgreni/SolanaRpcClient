#pragma once
#include <string>
#include "Solana/Core/Network/HttpClient.hpp"
#include "Solana/Rpc/Methods/GetBalance.hpp"
#include "Solana/Rpc/Methods/GetBlockHeight.hpp"
#include "Solana/Rpc/Methods/GetBlock.hpp"
#include "Solana/Rpc/Methods/GetBlockTime.hpp"
#include "Solana/Rpc/Methods/GetBlocksWithLimit.hpp"
#include "Solana/Rpc/Methods/GetBlocks.hpp"
#include "Solana/Rpc/Methods/GetBlockProduction.hpp"
#include "Solana/Rpc/Methods/GetBlockCommitment.hpp"
#include "Solana/Rpc/Methods/GetAccountInfo.hpp"
#include "Solana/Rpc/Methods/GetTransaction.hpp"
#include "Solana/Rpc/Methods/GetLatestBlockhash.hpp"
#include "Solana/Rpc/Methods/GetSlot.hpp"
#include "Solana/Rpc/Methods/SimulateTransaction.hpp"
#include "Solana/Rpc/Methods/SendTransaction.hpp"
#include "Solana/Rpc/Methods/RequestAirdrop.hpp"
#include "Solana/Rpc/Methods/WithJsonReply.hpp"

namespace Solana {
    class Rpc {
    public:
        Rpc(const std::string & endpoint)
            : client(endpoint) {}

        template<typename T>
        std::future<RpcReply<T>> send(const T & req) {
            auto j = json();

            j["jsonrpc"] = "2.0";
            j["id"] = "1";
            j["method"] = req.methodName();
            if (req.hasParams())
                j["params"] = req.toJson();

#if !NDEBUG
            #include <iostream>
            std::cout << "SENDING: " << j.dump() << "\n";
#endif

            auto res = client.post<RpcReply<T>>(j);
            return res;
        }
    private:
        Network::HttpClient client;
    };
}

