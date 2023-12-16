#pragma once
#include "RpcMethod.hpp"
#include <string>
#include "Common.hpp"

namespace Solana {
    struct GetBlockProduction : RpcMethod {

        struct Reply {
            json data;
        };

        struct Config {
            Commitment commitment;
            std::optional<std::string> identity;
            std::optional<
                std::pair<int64_t, int64_t>> range;
        };

        explicit GetBlockProduction(const Config & config = {})
            : config(config) {}

        Config config;
    };
}