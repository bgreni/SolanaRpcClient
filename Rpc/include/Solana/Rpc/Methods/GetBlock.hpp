#pragma once
#include "RpcMethod.hpp"
#include "Common.hpp"

namespace Solana {
    struct GetBlock : RpcMethod {
        struct Reply {
            json blockData;
        };

        static Reply parseReply(const json & data) {
            return Reply {
                .blockData = data["result"]
            };
        }

        struct Config {
            Commitment commitment;
            AccountEncoding encoding;
        };

        GetBlock(int64_t slot, const Config & config = {}) :
            slot(slot),
            config(config)
        {}

        json toJson() const override {
            auto ob = json::object();
            config.commitment.addToJson(ob);
            config.encoding.addToJson(ob);
            return json::array({
                slot,
                ob
            });
        }

        std::string methodName() const override { return "getBlock"; }

    private:
        int64_t slot;
        Config config;
    };
}