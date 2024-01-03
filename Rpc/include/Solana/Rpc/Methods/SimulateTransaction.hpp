#pragma once
#include "Solana/Core/Types/Types.hpp"
#include "RpcMethod.hpp"
#include "Solana/Core/Transaction/Transaction.hpp"

namespace Solana {
    struct SimulateTransaction : public RpcMethod {
        using Reply = json;

        static Reply parseReply(const json & j) {

            return j["result"];
        }

        explicit SimulateTransaction(
            const Txn & txn)
        : txn(txn.serialize().toString())
        {}

        explicit SimulateTransaction(const std::string & txn)
        : txn(txn) x{}
        std::string methodName() const override { return "simulateTransaction"; }

        json toJson() const override {
            return json::array({
                txn
            });
        }

        std::string txn;
    };
}