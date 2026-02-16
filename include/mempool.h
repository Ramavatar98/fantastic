#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <queue>

namespace bnc {
    struct Transaction {
        std::string txid;                           // Transaction ID (SHA256 hash)
        uint32_t version;                           // Transaction version
        std::vector<std::pair<std::string, uint32_t>> inputs;  // {txid, index}
        std::vector<std::pair<std::string, uint64_t>> outputs; // {address, amount}
        uint32_t locktime;                          // Lock time
        uint64_t timestamp;                         // Transaction timestamp
        std::string signature;                      // Digital signature (hex)
        
        // Serialization
        std::vector<uint8_t> serialize() const;
        static Transaction deserialize(const std::vector<uint8_t>& data);
        std::string calculate_txid() const;
    };
    
    class Mempool {
    private:
        std::map<std::string, Transaction> transactions;  // txid -> Transaction
        std::queue<std::string> priority_queue;           // Priority order
        static constexpr size_t MAX_SIZE = 10000;
        
    public:
        Mempool();
        ~Mempool();
        
        // Transaction operations
        bool add_transaction(const Transaction& tx);
        bool remove_transaction(const std::string& txid);
        Transaction get_transaction(const std::string& txid) const;
        std::vector<Transaction> get_transactions(size_t count) const;
        
        // Status
        size_t size() const;
        bool contains(const std::string& txid) const;
        
        // Persistence
        bool save_to_file(const std::string& filepath);
        bool load_from_file(const std::string& filepath);
    };
}

#endif // MEMPOOL_H
