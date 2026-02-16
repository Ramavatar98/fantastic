#ifndef SIGNATURES_H
#define SIGNATURES_H

#include <string>
#include <vector>
#include <cstdint>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>

namespace bnc {
    class KeyPair {
    private:
        EC_KEY* key;
        std::string private_key_hex;
        std::string public_key_hex;
        
    public:
        KeyPair();
        ~KeyPair();
        
        // Key generation
        bool generate_key();
        
        // Getters
        std::string get_private_key() const;
        std::string get_public_key() const;
        
        // Import/Export
        bool import_private_key(const std::string& hex);
        bool export_keys();
    };
    
    class DigitalSignature {
    public:
        DigitalSignature();
        ~DigitalSignature();
        
        // Signing
        std::string sign_message(const std::string& message, const std::string& private_key_hex);
        
        // Verification
        bool verify_signature(const std::string& message, const std::string& signature_hex, 
                             const std::string& public_key_hex);
        
        // Hashing
        static std::string sha256(const std::string& data);
        static std::string sha256(const std::vector<uint8_t>& data);
        
    private:
        EVP_MD_CTX* md_ctx;
    };
} // namespace bnc

#endif // SIGNATURES_H
