#pragma once

#include "Solana/Core/Account/Account.hpp"

namespace Solana::Programs::Token {
    enum TokenAccountState : u8 {
        Uninitialized,
        Initialized,
        Frozen
    };

    LAYOUT(Mint,
    (std::optional<Pubkey>, mintAuthority),
    (u64, supply),
    (u8, decimals),
    (bool, isInitialized),
    (std::optional<Pubkey>, freezeAuthority))

    LAYOUT(Account,
    (Pubkey, mint),
    (Pubkey, owner),
    (u64, amount),
    (std::optional<Pubkey>, delegate),
    (TokenAccountState, state),
    (std::optional<u64>, isNative),
    (u64, delegatedAmount),
    (std::optional<Pubkey>, closeAuthority))
}