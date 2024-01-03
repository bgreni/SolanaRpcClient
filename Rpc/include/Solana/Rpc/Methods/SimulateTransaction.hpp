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

        struct SimReturnAccounts {
            std::vector<std::string> addresses;
            EncodingType encodingType;
        };

        struct Config {
            Commitment commitment;
            RPCPARAM(bool, sigVerify);
            RPCPARAM(bool, replaceRecentBlockHash);
            MinContextSlot minContextSlot;
            TransactionEncoding encodingType;
            std::optional<SimReturnAccounts> accounts;
        };

        explicit SimulateTransaction(const Txn & txn, const Config & config = {}) {
            std::string encodedTxn{};
            if (config.encodingType) {
                if (*config.encodingType == TransactionEncoding::str(EncodingType::Base58)) {
                    encodedTxn = txn.serialize().toString();
                } else if (*config.encodingType == TransactionEncoding::str(EncodingType::Base64)) {
                    encodedTxn = txn.serialize().toBase64();
                } else {
                    throw std::runtime_error("Invalid txn encoding: " + *config.encodingType);
                }
            }
            this->txn = encodedTxn;
            this->config = config;
        }

        explicit SimulateTransaction(const std::string & txn, const Config = {})
        : txn(txn), config(config) {}
        std::string methodName() const override { return "simulateTransaction"; }

        json toJson() const override {
            auto c = json::object();
            config.commitment->addToJson(c);
            if (config.si)
            return json::array({
                txn,
            });
        }

        std::string txn;
        Config config;
    };
}