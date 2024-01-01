#pragma once
#include "Solana/Core/Types/Types.hpp"
#include "RpcMethod.hpp"

namespace Solana {
    struct GetLatestBlockhash : public RpcMethod {

        using Reply = json;

        static Reply parseReply(const json & j) {
            return j["result"];
        }

        explicit GetLatestBlockhash() = default;

        json toJson() const override {return {};}

        std::string methodName() const override { return "getLatestBlockhash"; }

        bool hasParams() const override { return false;}

    };
}
