#pragma once
#include "Solana/Core/Types/Types.hpp"
#include "Solana/Core/Util/Constants.hpp"

namespace Solana {
    class Utils {
    public:
        static constexpr u64 SolToLamports(u64 sol) { return sol * LAMPORTS_PER_SOL; };
        static constexpr u64 SolToLamports(f64 sol) { return static_cast<u64>(sol * static_cast<f64>(LAMPORTS_PER_SOL)); }
    };
}
