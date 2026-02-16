#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <vector>

namespace bnc {
    class AddressGenerator {
    public:
        AddressGenerator();
        
        // Address generation from public key
        static std::string generate_address(const std::string& public_key_hex);
        
        // Address validation
        static bool is_valid_address(const std::string& address);
        
        // Encoding/Decoding
        static std::string encode_base58(const std::vector<uint8_t>& data);
        static std::vector<uint8_t> decode_base58(const std::string& encoded);
        
    private:
        static constexpr const char* BASE58_ALPHABET = 
            "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    };
}

#endif // ADDRESS_H