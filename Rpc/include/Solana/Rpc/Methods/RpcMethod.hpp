#pragma once
#include "nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;


namespace Solana {
    struct RpcMethod {
        virtual json toJson() const = 0;
        virtual std::string methodName() const = 0;
        virtual bool hasParams() const { return true; }
    };

    template<typename T>
    struct RpcReply {
        std::string jsonrpc;
        std::string id;
        typename T::Reply result;

        static RpcReply<T> parse(std::string_view data) {
            const auto j = json::parse(data);
            if (j.contains("error")) throw std::runtime_error("you got an error kid");
            return RpcReply {
                .jsonrpc = j["jsonrpc"],
                .id = j["id"].get<std::string>(),
                .result = T::Reply::parse(j)
            };
        }
    };
}