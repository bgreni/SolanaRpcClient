#pragma once
#include <string>
#include <cpprest/json.h>

namespace SolanaRpc {
    struct CommitmentConfig {
        std::string commitment = "finalized";
    };
}
