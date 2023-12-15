#pragma once

#include "RpcMethod.hpp"
#include <string>

namespace Solana {
    struct GetBlockHeight : RpcMethod {
        struct Reply {
            int64_t height;
        };
        GetBlockHeight() = default;

        static Reply parseReply(const json & data) {
            return Reply{.height = data["result"].get<int64_t>()};
        }

        json toJson() const override { return {}; }
        bool hasParams() const override { return false; }
        std::string methodName() const override { return "getBlockHeight"; };
    };
}