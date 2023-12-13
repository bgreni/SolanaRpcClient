#pragma once
#include "RpcMethod.hpp"
#include <optional>
#include <string>

namespace Solana {
    struct GetAccountInfo : RpcMethod {

        struct Config {
            Config() = default;
            std::optional<std::string> commitment;
            std::optional<std::string> encoding;
        };

        std::string methodName() const override { return "getAccountInfo"; }

        json toJson() const override {
            json c = {};
            if (config.commitment.has_value()) {
                c["commitment"]
            }
        }

        std::string key;
        Config config = Config();
    };
}