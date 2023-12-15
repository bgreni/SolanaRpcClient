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
        Json,
        JsonParsed,
        Base58,
        Base64
    };

    struct Encoding : ConfigParam<std::string> {
        template<typename T>
        Encoding(const T & val) : ConfigParam<std::string>(val) {}
        Encoding(EncodingType type)
            : ConfigParam<std::string>([type]() {
                switch (type) {
                    case Json:
                        return "json";
                    case JsonParsed:
                        return "jsonParsed";
                    case Base58:
                        return "base58";
                    case Base64:
                        return "base64";
                }
            }())
        {}

        Encoding() = default;

        std::string name() const override {return "encoding";}
    };
}

