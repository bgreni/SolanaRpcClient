#pragma once

#include "RpcMethod.hpp"
#include <string>
#include <string_view>
#include <iostream>
#include <optional>

namespace Solana {
    struct GetBalance : RpcMethod {

        struct Reply {
            int64_t value;
        };

        struct Config {
            std::optional<std::string> commitment;
            std::optional<int64_t> minContextSlot;
        };

        explicit GetBalance(const std::string & address, const Config & config = {}) : address(address), config(config) {}

        static Reply parseReply(const json & data) {
            return Reply {.value = data["result"]["value"].get<int64_t>()};
        }

        json toJson() const override {
            json c = {};
            if (config.commitment.has_value()) {
                c["commitment"] = *config.commitment;
            }

            if (config.minContextSlot.has_value()) {
                c["minContextSlot"] = *config.minContextSlot;
            }
            return json::array({
                json(address),
                c
            });
        }

        std::string methodName() const override { return "getBalance"; };

    private:
        std::string address;
        Config config;
    };
}