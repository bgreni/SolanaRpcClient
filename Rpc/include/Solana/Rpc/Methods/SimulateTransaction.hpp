#pragma once
#include "Solana/Core/Types/Types.hpp"
#include "RpcMethod.hpp"

namespace Solana {
    struct SimulateTransaction : public RpcMethod {
        struct Reply {
            json result;
        };

        static Reply parseReply(const json & j) {
            return Reply {
                .result = j["result"]
            };
        }

        explicit SimulateTransaction(const std::string & txn)
        : txn(txn) {}
        std::string methodName() const override { return "simulateTransaction"; }

        json toJson() const override {
            return json::array({
                txn
            });
        }

        std::string txn;
    };
}