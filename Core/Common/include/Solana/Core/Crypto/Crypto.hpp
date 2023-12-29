#pragma once
#include <array>
#include <string_view>
#include "Solana/Core/Types/Types.hpp"

namespace Solana::Crypto {
    class Keypair {
    public:
        Keypair(Pubkey pubKey, PrivateKey pk) : pubkey(pubKey), privateKey(pk){}

        static Keypair generateKeyPair();
        static Keypair fromSecretKey(std::string_view sk);
//        static Keypair fromPrivateKey(std::string_view pk);

        Pubkey pubkey;
        PrivateKey privateKey;
    };
}