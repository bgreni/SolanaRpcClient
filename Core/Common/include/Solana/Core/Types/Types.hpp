#pragma once
#include <type_traits>
#include <string>
#include <array>
#include <boost/multiprecision/cpp_int.hpp>
#include "Solana/Core/Encoding/Base58.hpp"
// Using the anchor documentation space reference https://www.anchor-lang.com/docs/space

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

    class Buffer : public std::vector<u8> {
        void serialize(std::vector<u8> & out) const {
            for (auto byte : *this) {
                out.push_back(byte);
            }
        }
    };

    template<int T>
    class Bytes : public std::array<u8, T> {
    public:
        void serialize(std::vector<u8> & out) const {
            for (auto it = this->cbegin(); this->cbegin() != this->cend(); ++it) {
                out.push_back(*it);
            }
        }
    };

    class Pubkey : public Bytes<32> {
    public:
        std::string toStdString() {
            return Encoding::Base58::Encode(std::string{(const char *)this->data(), 32});
        }
        static Pubkey fromString(const std::string & str) {
            const auto decoded = Encoding::Base58::Decode(str);

        }
    };

    class PrivateKey : public Bytes<32>{};

    template<typename T>
    struct BytesNeeded {
    static const int value = sizeof(T);
    };

    template<>
    struct BytesNeeded<Solana::Pubkey> {
        static const int value = 32;
    };

    template<int T>
    struct BytesNeeded<Solana::Bytes<T>> {
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