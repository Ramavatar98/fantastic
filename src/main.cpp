#include <iostream>
#include "blockchain.h"
#include "utxo.h"
#include "mempool.h"
#include "signatures.h"
#include "address.h"
#include "p2p.h"
#include "config.h"
#include <filesystem>

using namespace bnc;

int main() {
    std::cout << "=== Bitnotcoin (BNC) Node ===" << std::endl;
    std::cout << "Initial Reward: " << (INITIAL_REWARD / 100000000) << " BNC" << std::endl;
    std::cout << "Block Time: " << (BLOCK_TIME_MS / 1000) << " seconds" << std::endl;
    std::cout << "Halving Interval: " << HALVING_INTERVAL << " blocks" << std::endl;
    
    std::filesystem::create_directories("data");
    
    Blockchain blockchain;
    UTXOManager utxo_manager;
    Mempool mempool;
    P2PNetwork network(DEFAULT_PORT);
    
    std::cout << "\n[*] Initializing blockchain..." << std::endl;
    if (blockchain.load_from_file(BLOCKCHAIN_PATH)) {
        std::cout << "[+] Blockchain loaded. Height: " << blockchain.get_height() << std::endl;
    } else {
        std::cout << "[*] Creating genesis block..." << std::endl;
        Block genesis;
        genesis.block_height = 0;
        genesis.block_reward = INITIAL_REWARD;
        blockchain.add_block(genesis);
        blockchain.save_to_file(BLOCKCHAIN_PATH);
    }
    
    std::cout << "\n[*] Generating keypair..." << std::endl;
    KeyPair keypair;
    if (keypair.generate_key()) {
        std::cout << "[+] Keypair generated successfully" << std::endl;
        std::string pub_key = keypair.get_public_key();
        
        std::string address = AddressGenerator::generate_address(pub_key);
        std::cout << "[+] Address: " << address << std::endl;
        
        if (AddressGenerator::is_valid_address(address)) {
            std::cout << "[+] Address validated successfully" << std::endl;
        }
    }
    
    std::cout << "\n[*] Loading UTXO set..." << std::endl;
    if (utxo_manager.load_from_file(UTXO_PATH)) {
        std::cout << "[+] UTXO set loaded" << std::endl;
    } else {
        std::cout << "[*] Creating new UTXO set..." << std::endl;
    }
    
    std::cout << "\n[*] Loading mempool..." << std::endl;
    if (mempool.load_from_file(MEMPOOL_PATH)) {
        std::cout << "[+] Mempool loaded. Size: " << mempool.size() << std::endl;
    }
    
    std::cout << "\n[*] Initializing P2P network..." << std::endl;
    std::cout << "[+] Node ID: " << network.get_node_id() << std::endl;
    std::cout << "[+] Listen Port: " << DEFAULT_PORT << std::endl;
    
    network.add_peer("127.0.0.1", 8334);
    network.add_peer("127.0.0.1", 8335);
    std::cout << "[+] Peer count: " << network.get_peer_count() << std::endl;
    
    std::cout << "\n[*] Block Reward Schedule:" << std::endl;
    for (uint32_t height = 0; height <= 200000; height += HALVING_INTERVAL) {
        uint64_t reward = blockchain.get_block_reward(height);
        std::cout << "  Block " << height << ": " << (reward / 100000000) << " BNC" << std::endl;
    }
    
    std::cout << "\n[*] Saving state..." << std::endl;
    blockchain.save_to_file(BLOCKCHAIN_PATH);
    utxo_manager.save_to_file(UTXO_PATH);
    mempool.save_to_file(MEMPOOL_PATH);
    std::cout << "[+] State saved successfully" << std::endl;
    
    std::cout << "\n=== BNC Node Ready ===" << std::endl;
    return 0;
}