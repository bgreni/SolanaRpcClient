#pragma once

#include "RpcMethod.hpp"
#include <string>

namespace Solana {
    struct GetBlockHeight : RpcMethod {
        struct Reply {
            static Reply parse(const json & data) {
                return Reply{.height = data["result"].get<int64_t>()};
            }
            int64_t height;
        };
        GetBlockHeight() = default;

        json toJson() const override { return {}; }
        bool hasParams() const override { return false; }
        std::string methodName() const override { return "getBlockHeight"; };
    };
}