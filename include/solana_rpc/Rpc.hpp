#pragma once
#include <string>
#include "HttpClient.hpp"
#include "solana_rpc/methods/GetBalance.hpp"
#include <concepts>

template<class T, class M>
concept Derived = std::is_base_of<M, T>::value;

namespace SolanaRpc {
    class Rpc {
    public:
        Rpc(const std::string & endpoint)
            : client(endpoint) {}

        Response getBalance(const GetBalance & req) {
            return send<GetBalance, Response>(req);
        }
    private:
        template<Derived<RpcMethod> T, typename K>
        K send(const T & req) {
//            obj["jsonrpc"] = web::json::value(U("2.0"));
//            obj[U("id")] = web::json::value(U("1"));
//            obj[U("method")] = web::json::value(U("getBalance"));
//            obj[U("params")] = req.toJson();
            auto j = json();
            auto params = json();
            to_json(j, params);
            j["jsonrpc"] = "2.0";
            j["id"] = "1";
            j["method"] = "getBalance";
            j["params"] = params.dump();
            auto res = client.post(j);
//            auto json = client.post(obj)
//                .get()
//                .extract_json()
//                .get();
            return res.get();
//            return T::parseReturn(json);
        }
    private:
        HttpClient client;
    };
}

