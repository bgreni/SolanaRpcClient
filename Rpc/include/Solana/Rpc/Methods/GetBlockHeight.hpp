#pragma once

#include "RpcMethod.hpp"
#include <string>

namespace Solana {
    struct GetBlockHeight : RpcMethod {
        struct Reply {
            int64_t height;
        };

        struct Config {
            Commitment commitment;
            MinContextSlot minContextSlot;
        };

        GetBlockHeight(const Config & config = {}) : config(config){}

        static Reply parseReply(const json & data) {
            return Reply{.height = data["result"].get<int64_t>()};
        }

        json toJson() const override {
            auto c = json();
            config.commitment.addToJson(c);
            config.minContextSlot.addToJson(c);
            return c;
        }
        bool hasParams() const override { return false; }
        std::string methodName() const override { return "getBlockHeight"; };

        Config config;
    };
}