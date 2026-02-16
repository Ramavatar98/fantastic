#ifndef P2P_H
#define P2P_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <map>

namespace bnc {
    struct PeerInfo {
        std::string ip;
        uint16_t port;
        uint64_t last_seen;
        bool is_connected;
        std::string version;
    };
    
    class P2PNetwork {
    private:
        std::map<std::string, PeerInfo> peers;  // peer_id -> PeerInfo
        std::string node_id;
        uint16_t listen_port;
        
    public:
        P2PNetwork(uint16_t port = 8333);
        ~P2PNetwork();
        
        // Peer management
        bool add_peer(const std::string& ip, uint16_t port);
        bool remove_peer(const std::string& peer_id);
        std::vector<PeerInfo> get_peers() const;
        
        // Network operations
        bool broadcast_transaction(const std::string& tx_data);
        bool broadcast_block(const std::string& block_data);
        bool sync_blockchain();
        
        // Connection management
        bool connect_to_peer(const std::string& ip, uint16_t port);
        bool disconnect_from_peer(const std::string& peer_id);
        
        // Status
        size_t get_peer_count() const;
        std::string get_node_id() const;
    };
}

#endif // P2P_H