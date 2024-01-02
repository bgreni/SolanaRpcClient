
#pragma once
#include "Solana/Core/Transaction/Instruction.hpp"
#include "Transaction.hpp"
#include <memory>
#include <vector>
#include <set>
#include "Solana/Core/Crypto/Crypto.hpp"

namespace Solana::Transaction {

    template<class T>
    concept IsInstruction = std::is_base_of<ConcreteInstruction, T>::value;

    class TransactionBuilder {
    public:
        TransactionBuilder(const BlockHash & recentHash, Pubkey feepayer)
            : recentBlockHash(recentHash), feePayer(feepayer){}

        template<IsInstruction T>
        TransactionBuilder & add(const T & instruction) {
            return add(instruction.toInstruction());
        }

        TransactionBuilder & add(const Instruction & instruction) {
            instructions.push_back(instruction);
            return *this;
        }

        Txn build() {
            return Txn(
                sigs,
                compileMessage()
            );
        }

        Buffer serializeMessage();
        void sign(const Solana::Crypto::Keypair & kp);
        Message compileMessage();


    private:
        BlockHash recentBlockHash;
        Signatures sigs;
        std::vector<Pubkey> signers;
        std::vector<Instruction> instructions;
        Pubkey feePayer;
    };
}
