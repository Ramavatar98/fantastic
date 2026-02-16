#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

namespace bnc {
    // Blockchain Parameters
    constexpr uint64_t INITIAL_REWARD = 25 * 100000000;  // 25 BNC in Not
    constexpr uint64_t BLOCK_TIME_MS = 60000;             // 1 minute in milliseconds
    constexpr uint32_t HALVING_INTERVAL = 100000;         // blocks
    constexpr uint64_t MAX_SUPPLY = 21000000 * 100000000; // 21M BNC in Not
    
    // Address Parameters
    constexpr char ADDRESS_PREFIX = 'B';
    constexpr uint8_t ADDRESS_VERSION = 0x00;
    constexpr size_t ADDRESS_LENGTH = 34;  // 1 prefix + 32 bytes hash + 1 checksum
    
    // Storage
    constexpr const char* BLOCKCHAIN_PATH = "data/blockchain.dat";
    constexpr const char* UTXO_PATH = "data/utxo.dat";
    constexpr const char* MEMPOOL_PATH = "data/mempool.dat";
    
    // Network
    constexpr uint16_t DEFAULT_PORT = 8333;
    constexpr size_t MAX_CONNECTIONS = 100;
}

#endif // CONFIG_H
