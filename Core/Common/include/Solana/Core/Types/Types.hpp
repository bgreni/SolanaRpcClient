#pragma once
#include <type_traits>
#include <string>
#include <array>
#include <boost/multiprecision/cpp_int.hpp>
#include "Solana/Core/Encoding/Base58.hpp"
// Using the anchor documentation space reference https://www.anchor-lang.com/docs/space

// TODO: SUPPORT 128 bit int
namespace Solana {
    using u8 = uint8_t;
    using i8 = int8_t;
    using u16 = uint16_t;
    using i16 = int16_t;
    using u32 = uint32_t;
    using i32 = int32_t;
    using u64 = uint64_t;
    using i64 = int64_t;
    using f32 = float;
    using f64 = double;
    using u128 = boost::multiprecision::uint128_t;
    using i128 = boost::multiprecision::int128_t;

    template<int T>
    class String : public std::array<unsigned char, T> {
    public:
        std::string toStdString() {
            return Encoding::Base58::Encode(std::string{(const char *)this->data(), T});
        }
    };

    class PubKey : public String<32> {
    };

    class PrivateKey : public String<32>{};

    template<typename T>
    struct BytesNeeded {
    static const int value = sizeof(T);
    };

    template<>
    struct BytesNeeded<Solana::PubKey> {
        static const int value = 32;
    };

    template<int T>
    struct BytesNeeded<Solana::String<T>> {
        static const int value = T + 4;
    };

    template<>
    struct BytesNeeded<bool> {
        static const int value = 1;
    };

    template<>
    struct BytesNeeded<Solana::u8> {
        static const int value = 1;
    };

    template<>
    struct BytesNeeded<Solana::i8> {
        static const int value = 1;
    };

    template<>
    struct BytesNeeded<Solana::u16> {
        static const int value = 2;
    };

    template<>
    struct BytesNeeded<Solana::i16> {
        static const int value = 2;
    };

    template<>
    struct BytesNeeded<Solana::u32> {
        static const int value = 4;
    };

    template<>
    struct BytesNeeded<Solana::i32> {
        static const int value = 4;
    };

    template<>
    struct BytesNeeded<Solana::u64> {
        static const int value = 8;
    };

    template<>
    struct BytesNeeded<Solana::i64> {
        static const int value = 8;
    };

    template<>
    struct BytesNeeded<Solana::u128> {
        static const int value = 16;
    };

    template<>
    struct BytesNeeded<Solana::i128> {
        static const int value = 16;
    };

    template<>
    struct BytesNeeded<Solana::f32> {
        static const int value = 4;
    };

    template<>
    struct BytesNeeded<Solana::f64> {
        static const int value = 8;
    };

    template<>
    struct BytesNeeded<std::in_place_t> {
        static const int value = 0;
    };

    template<typename T>
    struct BytesNeeded<std::optional<T>> {
        static const int value = BytesNeeded<T>::value + 4;
    };
}