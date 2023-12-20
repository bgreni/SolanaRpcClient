#include "Solana/Core/Crypto/Crypto.hpp"
#include <openssl/evp.h>
#include "Solana/Core/Encoding/Base58.hpp"
#include <iostream>


using namespace Solana::Crypto;

Keypair Keypair::generateKeyPair() {
    EVP_PKEY * pKey = nullptr;
    auto * ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_keygen(ctx, &pKey);

    size_t pubKeylen;
    EVP_PKEY_get_raw_public_key(pKey, nullptr, &pubKeylen);

    PubKey pubKey;
    EVP_PKEY_get_raw_public_key(pKey, pubKey.data(), &pubKeylen);

    size_t privKeyLen;
    EVP_PKEY_get_raw_private_key(pKey, nullptr, &privKeyLen);
    PrivateKey privKey;
    EVP_PKEY_get_raw_private_key(pKey, privKey.data(), &privKeyLen);

    EVP_PKEY_CTX_free(ctx);

    return {pubKey, privKey};
}

Keypair Keypair::fromSecretKey(std::string_view sk) {
    auto ret = Solana::Encoding::Base58::Decode(sk);
    PrivateKey privKey;
    std::copy_n(ret->begin(), 32, privKey.begin());
    PubKey pubKey;
    std::copy_n(ret->cbegin() + 32, 32, pubKey.begin());


    return {pubKey, privKey};
}

//std::pair<Key, Key> Keypair::fromPrivateKey(std::string_view pk) {
//    auto * ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, nullptr);
//    auto key = EVP
//}

