#pragma once
#include "RpcMethod.hpp"
#include <optional>
#include <string>
#include <array>
#include "Common.hpp"
#include "Solana/Core/Encoding/Base58.hpp"
#include "Solana/Core/Encoding/Base64.hpp"

template<typename T>
struct is_json {
    static const bool value = false;
};

template<>
struct is_json<json> {
    static const bool value = false;
};

namespace Solana {

    // TODO: support base64+ztd encoded accounts
    template<typename AccountStruct = json>
    struct GetAccountInfo : RpcMethod {

        struct Reply {
            bool executable;
            int64_t lamports;
            std::string owner;
            int64_t rentEpoch;
            int64_t space;
            AccountStruct accountData;
        };

        static Reply parseReply(const json & j) {
            const auto d = j["result"]["value"];
            auto data = d["data"];

            auto account = AccountStruct();
            if constexpr (is_json<AccountStruct>::value) {
                account = data;
            } else {
                std::vector<unsigned char> dataBytes{};
                std::string accountData;
                std::string dataEncoding = "base58";
                if (data.is_array()) {
                    accountData = data[0].get<std::string>();
                    dataEncoding = data[1].get<std::string>();
                } else {
                    accountData = data.get<std::string>();
                }

                if (dataEncoding == "jsonParsed") {
                    throw std::runtime_error("jsonParsed should be used the default json return type");
                }

                if (dataEncoding == "base58") {
                    const auto decoded = Encoding::Base58::Decode(
                        accountData);
                    account.decode(decoded);
                }
                else if (dataEncoding == "base64") {
                    std::string out;
                    auto error = Encoding::Base64::Decode(accountData, out);
                    if (!error.empty()) {
                        throw std::runtime_error("Failed to decode base64 string: " + error);
                    }
                    account.decode(out);
                }
                else {
                    throw std::runtime_error("Unsupported encoding type: " + dataEncoding);
                }
            }

            return Reply {
                    .accountData = account,
                    .executable = d["executable"].get<bool>(),
                    .lamports = d["lamports"].get<int64_t>(),
                    .rentEpoch = d["rentEpoch"].get<int64_t>(),
                    .space = d["space"].get<int64_t>()
            };
        }
        struct Config {
            Commitment commitment;
            AccountEncoding encoding;
        };

        explicit GetAccountInfo(const std::string & address, const Config & config = {})
            : key(address), config(config) {}

        std::string methodName() const override { return "getAccountInfo"; }

        json toJson() const override {
            auto ob = json::object();
            config.encoding.addToJson(ob);
            config.commitment.addToJson(ob);
            auto c = json::array({key, ob});

            return c;
        }

        std::string key;
        Config config = {};
    };
}