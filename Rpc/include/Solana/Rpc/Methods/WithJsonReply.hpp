#pragma once

#include "RpcMethod.hpp"

namespace Solana {
    template<typename T>
    struct WithJsonReply : RpcMethod {

        using Reply = json;

        static Reply parseReply(const json & data) {
            return data;
        }

        template <typename ...Args>
        WithJsonReply(Args ...args) : inner({args...}) {}

        std::string methodName() const override { return inner.methodName(); };
        json toJson() const override {
            return inner.toJson();
        }
    private:
        T inner;
    };
}