#include "../include/p2p.h"
#include <chrono>
#include <sstream>

namespace bnc {
    
    P2PNetwork::P2PNetwork(uint16_t port) : listen_port(port) {
        std::stringstream ss;
        ss << "node_" << std::chrono::system_clock::now().time_since_epoch().count();
        node_id = ss.str();
    }
    
    P2PNetwork::~P2PNetwork() {}
    
    bool P2PNetwork::add_peer(const std::string& ip, uint16_t port) {
        std::string peer_id = ip + ":" + std::to_string(port);
        if (peers.find(peer_id) != peers.end()) {
            return false;
        }
        
        PeerInfo peer;
        peer.ip = ip;
        peer.port = port;
        peer.last_seen = std::chrono::system_clock::now().time_since_epoch().count();
        peer.is_connected = false;
        peer.version = "1.0.0";
        
        peers[peer_id] = peer;
        return true;
    }
    
    bool P2PNetwork::remove_peer(const std::string& peer_id) {
        return peers.erase(peer_id) > 0;
    }
    
    std::vector<PeerInfo> P2PNetwork::get_peers() const {
        std::vector<PeerInfo> result;
        for (const auto& [id, peer] : peers) {
            result.push_back(peer);
        }
        return result;
    }
    
    bool P2PNetwork::broadcast_transaction(const std::string& tx_data) {
        return true;
    }
    
    bool P2PNetwork::broadcast_block(const std::string& block_data) {
        return true;
    }
    
    bool P2PNetwork::sync_blockchain() {
        return true;
    }
    
    bool P2PNetwork::connect_to_peer(const std::string& ip, uint16_t port) {
        std::string peer_id = ip + ":" + std::to_string(port);
        auto it = peers.find(peer_id);
        if (it != peers.end()) {
            it->second.is_connected = true;
            it->second.last_seen = std::chrono::system_clock::now().time_since_epoch().count();
            return true;
        }
        return false;
    }
    
    bool P2PNetwork::disconnect_from_peer(const std::string& peer_id) {
        auto it = peers.find(peer_id);
        if (it != peers.end()) {
            it->second.is_connected = false;
            return true;
        }
        return false;
    }
    
    size_t P2PNetwork::get_peer_count() const {
        return peers.size();
    }
    
    std::string P2PNetwork::get_node_id() const {
        return node_id;
    }
}