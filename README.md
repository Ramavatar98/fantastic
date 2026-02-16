# Bitnotcoin (BNC) - Decentralized Cryptocurrency

A complete C++ implementation of the Bitnotcoin (BNC) cryptocurrency for Termux and Linux systems.

## Features

- ✅ **UTXO Management** - Unspent Transaction Output tracking
- ✅ **Mempool** - Transaction memory pool with priority ordering
- ✅ **Digital Signatures** - OpenSSL-based ECDSA cryptography
- ✅ **Address Generation** - Base58 encoded addresses with 'B' prefix
- ✅ **P2P Network** - Peer-to-peer synchronization framework
- ✅ **Block Validation** - Full block header and transaction validation
- ✅ **Halving Logic** - Exponential reward halving every 100,000 blocks
- ✅ **Binary Storage** - Efficient data serialization

## Specifications

- **Initial Reward**: 25 BNC per block
- **Block Time**: 1 minute (60 seconds)
- **Halving Interval**: Every 100,000 blocks
- **Smallest Unit**: 1 Not = 0.00000001 BNC
- **Address Prefix**: 'B'
- **Max Supply**: 21,000,000 BNC
- **Total Nots**: 21 × 10^15

## Prerequisites

### Termux
```bash
pkg install clang openssl-dev cmake
```

### Ubuntu/Debian
```bash
sudo apt-get install build-essential libssl-dev cmake
```

### macOS
```bash
brew install openssl cmake
```

## Building

### Using CMake
```bash
mkdir build
cd build
cmake ..
make
```

### Using Make
```bash
make
```

### Cleaning
```bash
make clean
```

## Running

```bash
./bnc-node
```

## Project Structure

```
fantastic/
├── include/              # Header files
│   ├── config.h
│   ├── blockchain.h
│   ├── utxo.h
│   ├── mempool.h
│   ├── signatures.h
│   ├── address.h
│   └── p2p.h
├── src/                  # Implementation files
│   ├── main.cpp
│   ├── blockchain.cpp
│   ├── utxo.cpp
│   ├── mempool.cpp
│   ├── signatures.cpp
│   ├── address.cpp
│   └── p2p.cpp
├── data/                 # Blockchain data (created at runtime)
│   ├── blockchain.dat
│   ├── utxo.dat
│   └── mempool.dat
├── CMakeLists.txt
├── Makefile
└── README.md
```

## Module Descriptions

### Blockchain (`blockchain.h/cpp`)
Manages the main blockchain, including block creation, validation, and storage.

### UTXO Manager (`utxo.h/cpp`)
Tracks unspent transaction outputs with efficient binary storage.

### Mempool (`mempool.h/cpp`)
Maintains a pool of pending transactions with maximum size limits.

### Digital Signatures (`signatures.h/cpp`)
Implements ECDSA using OpenSSL with SHA256 hashing.

### Address Generator (`address.h/cpp`)
Creates and validates addresses with Base58 encoding and checksum verification.

### P2P Network (`p2p.h/cpp`)
Framework for peer-to-peer network synchronization and communication.

## Block Reward Schedule

| Block Range | Reward (BNC) |
|---|---|
| 0 - 99,999 | 25 BNC |
| 100,000 - 199,999 | 12.5 BNC |
| 200,000 - 299,999 | 6.25 BNC |
| 300,000 - 399,999 | 3.125 BNC |

## Binary File Formats

### blockchain.dat
- Header: 4 bytes (block count)
- For each block:
  - 4 bytes (block size)
  - Serialized block data

### utxo.dat
- Header: 4 bytes (address count)
- For each address:
  - 4 bytes (address length)
  - Address string
  - 4 bytes (UTXO count)
  - Serialized UTXO data

### mempool.dat
- Header: 4 bytes (transaction count)
- For each transaction:
  - 4 bytes (transaction size)
  - Serialized transaction data

## Usage Example

```cpp
// Initialize blockchain
bnc::Blockchain blockchain;

// Generate keypair
bnc::KeyPair keypair;
keypair.generate_key();

// Generate address
std::string address = bnc::AddressGenerator::generate_address(
    keypair.get_public_key()
);

// Get block reward at height 50000
uint64_t reward = blockchain.get_block_reward(50000);
```

## License

MIT License - Feel free to use for educational and commercial purposes.

## Author

Ramavatar98

## Contributing

Contributions are welcome! Please feel free to submit pull requests.

## Support

For issues, questions, or suggestions, please open an issue on GitHub.

---

**Happy Mining! 🚀**