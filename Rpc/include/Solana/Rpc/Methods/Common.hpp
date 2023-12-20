#pragma once
#include <optional>
#include <string>
#include "RpcMethod.hpp"

namespace Solana {

    template<typename T>
    struct ConfigParam : std::optional<T> {
        ConfigParam(const T & val) : std::optional<T>(val){}
        ConfigParam() : std::optional<T>(){};

        void addToJson(json & data) const {
            if (this->has_value()) {
                data[name()] = this->value();
            }
        }

        virtual std::string name() const = 0;
    };

    enum CommitmentLevel {
        Confirmed,
        Finalized
    };

    struct Commitment : ConfigParam<std::string> {

        template<typename T>
        Commitment(const T & val) : ConfigParam<std::string>(val){}
        Commitment(CommitmentLevel level)
            : ConfigParam<std::string>([level]() {
               switch (level) {
                   case Confirmed:
                       return "confirmed";
                   case Finalized:
                       return "finalized";
               }
            }())
        {}
        Commitment() = default;

        std::string name() const override {return "commitment";};
    };

    struct MinContextSlot : ConfigParam<int64_t> {

        template<typename T>
        MinContextSlot(const T & val) : ConfigParam<int64_t>(val){}
        MinContextSlot() = default;

        std::string name() const override { return "minContextSlot"; }
    };

    enum EncodingType {
        JsonParsed,
        Base58,
        Base64,
        Json
    };

    struct TransactionEncoding : ConfigParam<std::string> {
        template<typename T>
        TransactionEncoding(const T & val) : ConfigParam<std::string>(val) {}
        TransactionEncoding(EncodingType type)
            : ConfigParam<std::string>(str(type))
        {}

        static std::string str(EncodingType t) {
            switch (t) {
                case JsonParsed:
                    return "jsonParsed";
                case Base58:
                    return "base58";
                case Base64:
                    return "base64";
                case Json:
                    return "json";
                default:
                    throw std::runtime_error("Unsupported type");
            }
        }
        TransactionEncoding() = default;

        std::string name() const override {return "encoding";}
    };

    struct AccountEncoding : ConfigParam<std::string> {
        template<typename T>
        AccountEncoding(const T & val) : ConfigParam<std::string>(val) {}
        AccountEncoding(EncodingType type)
            : ConfigParam<std::string>(str(type))
        {}

        static std::string str(EncodingType t) {
            switch (t) {
                case JsonParsed:
                    return "jsonParsed";
                case Base58:
                    return "base58";
                case Base64:
                    return "base64";
                default:
                    throw std::runtime_error("Unsupported type");
            }
        }

        AccountEncoding() = default;

        std::string name() const override {return "encoding";}
    };
}

