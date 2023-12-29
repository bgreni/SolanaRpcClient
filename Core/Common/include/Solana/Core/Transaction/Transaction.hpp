#pragma once
#include "Solana/Core/Types/Types.hpp"
#include <vector>
#include "Message.hpp"
#include "CompactArray.hpp"

namespace Solana {
    class Txn {
    public:
        using Signatures = Transaction::CompactArray<Bytes<64>>;

        Buffer serialize() {
            auto b = Buffer();
            signatures.serialize(b);
            message.serialize(b);
            return b;
        }

    private:
        Signatures signatures;
        Transaction::Message message;
    };
}


