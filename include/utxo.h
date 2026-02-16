#ifndef UTXO_H
#define UTXO_H

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <memory>

namespace bnc {
    struct UTXO {
        std::string txid;           // Transaction ID (hex)
        uint32_t index;             // Output index
        uint64_t amount;            // Amount in Not
        std::string script_pubkey;  // Public key script
        uint32_t block_height;      // Block where UTXO was created
        
        // Serialization
        std::vector<uint8_t> serialize() const;
        static UTXO deserialize(const std::vector<uint8_t>& data);
    };
    
    class UTXOManager {
    private:
        std::map<std::string, std::vector<UTXO>> utxo_map;  // address -> UTXOs
        
    public:
        UTXOManager();
        ~UTXOManager();
        
        // UTXO operations
        void add_utxo(const std::string& address, const UTXO& utxo);
        void remove_utxo(const std::string& address, const std::string& txid, uint32_t index);
        std::vector<UTXO> get_utxos(const std::string& address) const;
        uint64_t get_balance(const std::string& address) const;
        
        // Persistence
        bool save_to_file(const std::string& filepath);
        bool load_from_file(const std::string& filepath);
        
        // Validation
        bool is_utxo_available(const std::string& txid, uint32_t index) const;
    };
}

#endif // UTXO_H