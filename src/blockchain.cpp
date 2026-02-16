#include "../include/blockchain.h"
#include "../include/signatures.h"
#include <fstream>
#include <algorithm>
#include <cmath>

namespace bnc {
    
    std::vector<uint8_t> BlockHeader::serialize() const {
        std::vector<uint8_t> data;
        data.insert(data.end(), (uint8_t*)&version, (uint8_t*)&version + 4);
        // Serialize other fields similarly
        return data;
    }
    
    BlockHeader BlockHeader::deserialize(const std::vector<uint8_t>& data) {
        BlockHeader header;
        // Deserialize implementation
        return header;
    }
    
    std::vector<uint8_t> Block::serialize() const {
        std::vector<uint8_t> data;
        auto header_data = header.serialize();
        data.insert(data.end(), header_data.begin(), header_data.end());
        return data;
    }
    
    Block Block::deserialize(const std::vector<uint8_t>& data) {
        Block block;
        // Deserialize implementation
        return block;
    }
    
    std::string Block::calculate_hash() const {
        auto serialized = header.serialize();
        return DigitalSignature::sha256(serialized);
    }
    
    Blockchain::Blockchain() : current_height(0), tip_hash("") {}
    
    Blockchain::~Blockchain() {}
    
    bool Blockchain::add_block(const Block& block) {
        if (!validate_block(block)) {
            return false;
        }
        
        chain.push_back(block);
        current_height++;
        tip_hash = block.calculate_hash();
        return true;
    }
    
    Block Blockchain::get_block(uint32_t height) const {
        if (height < chain.size()) {
            return chain[height];
        }
        return Block();
    }
    
    Block Blockchain::get_block_by_hash(const std::string& hash) const {
        for (const auto& block : chain) {
            if (block.calculate_hash() == hash) {
                return block;
            }
        }
        return Block();
    }
    
    bool Blockchain::validate_block(const Block& block) {
        if (!validate_block_header(block.header)) {
            return false;
        }
        
        // Validate transactions
        if (block.transactions.empty()) {
            return false;
        }
        
        return true;
    }
    
    bool Blockchain::validate_block_header(const BlockHeader& header) {
        // Check difficulty
        // Check timestamp
        // Check PoW
        return is_valid_pow(header);
    }
    
    uint64_t Blockchain::get_block_reward(uint32_t block_height) const {
        uint32_t halvings = block_height / HALVING_INTERVAL;
        uint64_t reward = INITIAL_REWARD;
        
        for (uint32_t i = 0; i < halvings && reward > 0; i++) {
            reward /= 2;
        }
        
        return reward;
    }
    
    uint32_t Blockchain::get_height() const {
        return current_height;
    }
    
    std::string Blockchain::get_tip_hash() const {
        return tip_hash;
    }
    
    double Blockchain::get_difficulty() const {
        // Calculate difficulty based on block times
        return 1.0;
    }
    
    bool Blockchain::save_to_file(const std::string& filepath) {
        std::ofstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        uint32_t size = chain.size();
        file.write((char*)&size, sizeof(size));
        
        for (const auto& block : chain) {
            auto serialized = block.serialize();
            uint32_t block_size = serialized.size();
            file.write((char*)&block_size, sizeof(block_size));
            file.write((char*)serialized.data(), block_size);
        }
        
        file.close();
        return true;
    }
    
    bool Blockchain::load_from_file(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        uint32_t size;
        file.read((char*)&size, sizeof(size));
        
        for (uint32_t i = 0; i < size; i++) {
            uint32_t block_size;
            file.read((char*)&block_size, sizeof(block_size));
            
            std::vector<uint8_t> block_data(block_size);
            file.read((char*)block_data.data(), block_size);
            
            Block block = Block::deserialize(block_data);
            chain.push_back(block);
            current_height++;
        }
        
        file.close();
        return true;
    }
    
    bool Blockchain::is_valid_pow(const BlockHeader& header) const {
        // Validate proof of work
        return true;
    }
    
    std::string Blockchain::calculate_merkle_root(const std::vector<std::string>& txids) const {
        if (txids.empty()) return "";
        
        std::vector<std::string> tree = txids;
        while (tree.size() > 1) {
            std::vector<std::string> next_level;
            for (size_t i = 0; i < tree.size(); i += 2) {
                std::string combined = tree[i];
                if (i + 1 < tree.size()) {
                    combined += tree[i + 1];
                } else {
                    combined += tree[i];
                }
                next_level.push_back(DigitalSignature::sha256(combined));
            }
            tree = next_level;
        }
        
        return tree[0];
    }
}