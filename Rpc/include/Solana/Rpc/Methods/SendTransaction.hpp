#pragma once
#include "Solana/Core/Types/Types.hpp"
#include "RpcMethod.hpp"
#include "Solana/Core/Transaction/Transaction.hpp"

namespace Solana {
    struct SendTransaction : public RpcMethod {

        // Reply structure
        using Reply = json;

        static Reply parseReply(const json & j) {
            return j["result"];
        }

        // Command impl

        explicit SendTransaction(
            const Txn & txn)
            : txn(txn.serialize().toString())
        {}

        explicit SendTransaction(const std::string & txn)
            : txn(txn) {}

        std::string methodName() const override { return "sendTransaction"; }

        json toJson() const override {
            return json::array({
               txn
           });
        }

        std::string txn;
    };
}
