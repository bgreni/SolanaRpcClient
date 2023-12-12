#pragma once

#include "RpcMethod.hpp"
#include <string>

namespace SolanaRpc {
    class GetBalance : RpcMethod {
    public:

        GetBalance(const std::string & address) : address(address){}
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetBalance, address)
//        web::json::value toJson() const override  {
//            return web::json::value::array(std::vector<web::json::value>{
//                web::json::value(address)
//            });
//        }
//        static int64_t parseReturn(web::json::value & v) {
//            return v[U("result")][U("value")].as_number().to_int64();
//        }
    private:
        std::string address;
    };
}