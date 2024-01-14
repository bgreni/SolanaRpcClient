# Solana Client SDK

A solana rpc client implementation built using Boost.Beast

Currently under heavy development

# Project Purpose
Solana developer tooling is currently highly focused on more modern languages like
Rust, Javascript, and Python (and for good reason), but it will forever remain true that
there is in fact a LOT of code out there written in C++. It's reasonable to expect that at some
point, some of the owners of that code might want to integrate with Solana (maybe). Although more likely 
people who prefer to use C++ for their high performance application needs might appreciate
good out-of-box tooling to target Solana for things like HFT algorithms.

This project is highly experimental and unstable, so keep that in mind for now if you intend on
using it.

# Examples

### Getting the latest blockhash
```C++
int main() {
    auto rpc = Rpc::DefaultMainnet();

    auto fut = rpc.send(GetLatestBlockhash());

    auto bHash = fut.get().result.blockHash;

    return 0;
}
```

### Subscribe to slot changes
```C++
int main() {
    auto rpc = Rpc(std::getenv("ENDPOINT"));
    
    auto id = rpc.onSlot([](const json & message) {
        print(message.dump(2, ' '));
    });

    return 0;
}
```