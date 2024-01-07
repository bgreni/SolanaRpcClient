#pragma once
#include "Solana/Core/Types/Types.hpp"
#include "RpcMethod.hpp"
#include "Common.hpp"

namespace Solana {
    class RequestAirdrop : public RpcMethod {
        using Reply = std::string;

        static Reply parseReply(const json & j) {
            return j["result"].get<std::string>();
        }

        struct Config {
            Commitment commitment;
        };

        explicit RequestAirdrop(
            const std::string & address,
            u64 amount,
            const Config & config = {})
            : address(address)
            , amount(amount)
            , config(config)
        {}

        std::string methodName() const override { return "requestAirdrop"; }

        json toJson() const override {
            auto c = json::object();
            config.commitment.addToJson(c);
            return json::array({
                address,
                amount,
                c
            });
        }

        std::string address;
        u64 amount;
        Config config;
    };
}
