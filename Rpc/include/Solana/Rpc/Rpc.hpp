#pragma once
#include <string>
#include "Solana/Core/Network/HttpClient.hpp"
#include "Solana/Rpc/Methods/GetBalance.hpp"
#include "Solana/Rpc/Methods/GetBlockHeight.hpp"
#include "Solana/Rpc/Methods/GetAccountInfo.hpp"




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
        HttpClient client;
    };
}

