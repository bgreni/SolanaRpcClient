#pragma once
#include "RpcMethod.hpp"
#include <optional>
#include <string>
#include <array>
#include "Common.hpp"

namespace Solana {
    struct GetAccountInfo : RpcMethod {

        // TODO: Deferring writing proper parsing for account data
        // as it could get a bit messy
        struct Reply {
//            std::array<std::string, 2> data;
//            bool executable;
//            int64_t lamports;
//            std::string owner;
//            int64_t rentEpoch;
//            int64_t space;
            json accountData;


        };

        static Reply parseReply(const json & data) {
            const auto d = data["result"]["value"];
            return Reply {
                    .accountData = d
//                    .data = {
//                            d["data"][0].get<std::string>(),
//                            d["data"][1].get<std::string>()
//                    },
//                    .executable = d["executable"].get<bool>(),
//                    .lamports = d["lamports"].get<int64_t>(),
//                    .rentEpoch = d["rentEpoch"].get<int64_t>(),
//                    .space = d["space"].get<int64_t>()

            };
        }

        struct Config {
            Commitment commitment;
            std::optional<std::string> encoding;
        };

        GetAccountInfo(std::string address) : key(address) {}



        std::string methodName() const override { return "getAccountInfo"; }

        json toJson() const override {
            auto ob = json::object();
            ob["encoding"] = "base64";
            auto c = json::array({key, ob});
//            if (config.commitment.has_value()) {
//                c["commitment"]
//            }

            return c;
        }

        std::string key;
        Config config = {};
    };
}